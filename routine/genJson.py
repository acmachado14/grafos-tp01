import json

with open("routine/grafos-txt/video.txt") as meu_txt:
    dados = meu_txt.read()


dados = dados.split()

jsonData = {"data": {"nodes": {"_data": []}, "edges": {"_data": []}}, "ponderado":True}

for j in range(int(dados[0])):
    jsonData["data"]["nodes"]["_data"].append(
        {
            "id": j+1,
            "label": f"{j+1}"
        }
    )

for i in range(1, (len(dados)-1), 3):
    jsonData["data"]["edges"]["_data"].append(
        {
            "from": int(dados[i]),
            "to": int(dados[i+1]),
            "label": dados[i+2]
        }
    )


with open("routine/grafos-json/arquivo.json", "w") as arquivo:     
    json.dump(jsonData, arquivo, indent=2)
