import json

with open("grafos-json/idLabel.json", encoding='utf-8') as meu_json:
    dados = json.load(meu_json)

arquivo = open('grafos-txt/idLabel.txt','w')

qtdNodes = len(dados['data']['nodes']['_data'])

arquivo.write(f"{qtdNodes} \n")

for i in dados['data']['edges']['_data']:
    data = dados['data']['edges']['_data'][str(i)]
    if 'label' in data:
        arquivo.write(f"{data['from']} {data['to']} {data['label']} \n")
    else:
        arquivo.write(f"{data['from']} {data['to']} {1} \n")

arquivo.close()