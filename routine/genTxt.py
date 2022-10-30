import json

with open("grafos-json/Djikstra.json", encoding='utf-8') as meu_json:
    dados = json.load(meu_json)

arquivo = open('grafos-txt/Djikstra.txt','w')

qtdNodes = len(dados['data']['nodes']['_data'])

arquivo.write(f"{qtdNodes} \n")

for i in dados['data']['edges']['_data']:
    data = dados['data']['edges']['_data'][str(i)]
    verticies = dados['data']['nodes']['_data']

    #achar id do vertice
    for j in verticies:
        if data['from'] == verticies[str(j)]['id']:
            vertice1 = verticies[str(j)]['label']
        if data['to'] == verticies[str(j)]['id']:
            vertice2 = verticies[str(j)]['label']
    
    if int(i) < len(dados['data']['edges']['_data']):
        if 'label' in data: #se for um grafo ponderado
            arquivo.write(f"{vertice1} {vertice2} {data['label']} \n")
        else:
            arquivo.write(f"{vertice1} {vertice2} {1} \n")
    else:
        if 'label' in data: #se for um grafo ponderado
            arquivo.write(f"{vertice1} {vertice2} {data['label']}")
        else:
            arquivo.write(f"{vertice1} {vertice2} {1}")

arquivo.close()