from flask import Flask, render_template, request, redirect, url_for
from flask_mysqldb import MySQL

app = Flask(__name__)

# Configurações do MySQL
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'pizzaria'

mysql = MySQL(app)

@app.route('/')
def index():
    # Consulta os pedidos do banco de dados
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT * FROM pedidos")
    pedidos = cursor.fetchall()
    cursor.close()
    return render_template('index.html', pedidos=pedidos)

@app.route('/novo_pedido', methods=['GET', 'POST'])
def novo_pedido():
    if request.method == 'POST':
        nome = request.form['nome']
        endereco = request.form['endereco']
        cep = request.form['cep']
        tipo_pizza = request.form['tipo_pizza']
        observacoes = request.form['observacoes']
        data_pedido = request.form['data_pedido']
        tipo_pagamento = request.form['tipo_pagamento']  
        
        # Consulta a tabela cardapio para obter os ingredientes da pizza selecionada
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT ingredientes FROM cardapio WHERE tipo_pizza = %s", (tipo_pizza,))
        ingredientes = cursor.fetchone()[0]
        cursor.close()
        
        cursor = mysql.connection.cursor()
        cursor.execute("INSERT INTO pedidos (nome, endereco, cep, tipo_pizza, observacoes, status_pedido, data_pedido, tipo_pagamento) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)", (nome, endereco, cep, tipo_pizza, observacoes, "Preparando Pedido", data_pedido, tipo_pagamento))
        mysql.connection.commit()
        cursor.close()
        
        # Obtenha o ID do pedido recém-cadastrado
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT LAST_INSERT_ID()")
        pedido_id = cursor.fetchone()[0]
        cursor.close()
        
        # Redirecione para a página pedido_info com o ID do pedido
        return redirect(url_for('pedido_info', pedido_id=pedido_id))
    
    return render_template('novo_pedido.html')

@app.route('/filtro_data', methods=['GET', 'POST'])
def filtro_data():
    if request.method == 'POST':
        # Lógica para filtrar os pedidos por data
        data_selecionada = request.form['data_selecionada']
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT * FROM pedidos WHERE data_pedido = %s", (data_selecionada,))
        pedidos = cursor.fetchall()
        cursor.close()
        return render_template('pedidos_por_data.html', pedidos=pedidos, data_selecionada=data_selecionada)
    
    return render_template('filtro_data.html')

@app.route('/pedido_info/<int:pedido_id>', methods=['GET', 'POST'])
def pedido_info(pedido_id):
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT * FROM pedidos WHERE id = %s", (pedido_id,))
    pedido = cursor.fetchone()
    cursor.close()
    
    if pedido is None:
        return "Pedido não encontrado"
    
    if request.method == 'POST':
        novo_status = request.form['novo_status']
        cursor = mysql.connection.cursor()
        cursor.execute("UPDATE pedidos SET status_pedido = %s WHERE id = %s", (novo_status, pedido_id))
        mysql.connection.commit()
        cursor.close()
        return redirect(url_for('pedido_info', pedido_id=pedido_id))
    
    # Mapeamento dos valores dos radios para os textos correspondentes
    tipo_pagamento_texto = {
        'Debito': 'Pagamento no Débito',
        'Credito': 'Pagamento no Crédito',
        'Pix': 'Pagamento no Pix',
        'Dinheiro': 'Pagamento em Dinheiro'
    }
    
    # Obtenha o texto do tipo de pagamento com base no valor do pedido
    tipo_pagamento = tipo_pagamento_texto.get(pedido[8], '')
    
    # Consulta a tabela cardapio para obter os ingredientes da pizza selecionada
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT ingredientes FROM cardapio WHERE tipo_pizza = %s", (pedido[4],))
    ingredientes = cursor.fetchone()[0]
    cursor.close()
    
    return render_template('pedido_info.html', pedido=pedido, tipo_pagamento=tipo_pagamento, ingredientes=ingredientes)

if __name__ == '__main__':
    app.run(debug=True)