import random

def gerar_arquivo_teste(nome_arquivo, num_rochas, peso_maximo, valor_maximo):
    """
    Gera um arquivo de teste no formato especificado.

    :param nome_arquivo: Nome do arquivo de saída (string)
    :param num_rochas: Número de rochas (int)
    :param peso_maximo: Valor máximo para o peso das rochas (int)
    :param valor_maximo: Valor máximo para o valor das rochas (int)
    """
    with open(nome_arquivo, 'w') as arquivo:
        # Escrever o número de rochas
        arquivo.write(f"{num_rochas}\n")
        
        # Gerar pesos e valores aleatórios para as rochas
        for _ in range(num_rochas):
            peso = random.randint(1, peso_maximo)
            valor = random.randint(1, valor_maximo)
            arquivo.write(f"{peso} {valor}\n")
    print(f"Arquivo de teste '{nome_arquivo}' gerado com sucesso!")

# Configurações
nome_arquivo = "testetp2_5.txt"
num_rochas = 100  # Quantidade de rochas
peso_maximo = 40  # Peso máximo de uma rocha
valor_maximo = 40  # Valor máximo de uma rocha

# Gerar o arquivo de teste
gerar_arquivo_teste(nome_arquivo, num_rochas, peso_maximo, valor_maximo)