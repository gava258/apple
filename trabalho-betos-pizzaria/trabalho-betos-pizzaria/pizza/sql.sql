create database pizzaria;


use pizzaria;

CREATE TABLE pedidos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    endereco VARCHAR(255) NOT NULL,
    cep VARCHAR(10) NOT NULL,
    tipo_pizza INT NOT NULL,
    observacoes TEXT,
    status_pedido VARCHAR(50),
    data_pedido DATE,
    tipo_pagamento TEXT
    
);

CREATE TABLE cardapio (
    tipo_pizza INT PRIMARY KEY,
    ingredientes VARCHAR(255) NOT NULL
);

INSERT INTO cardapio (tipo_pizza, ingredientes) VALUES 
(1, "queijo, peperoni"),
(2, "queijo, manjericão e tomate"),
(3, "queijo, catupiri e palmito"),
(4, "frango e catupiri"),
(5, "calabresa, queijo e queijo catupiri"),
(6, "milho, queijo, ervilha, ovo, oregano, presunto e cebola"),
(7, "cogumelo e queijo"),
(8, "queijo mussarela, queijo prato, queijo parmesão e queijo catupiri"),
(9, "queijo mussarela e queijo parmesão"),
(10, "atum e queijo");