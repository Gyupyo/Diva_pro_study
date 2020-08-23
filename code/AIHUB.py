import json
import codecs
import os

path_dir = './AIHUB'
out_text = open('AIHUB_TEXT.txt', 'w', -1, "utf-8")
out_ne = open('AIHUB_NE.txt', 'w', -1, "utf-8")

file_list = os.listdir(path_dir)
for file_name in file_list:
    with codecs.open(path_dir+ '/' + file_name, 'r', encoding='utf8') as json_file:
        json_data = json.load(json_file)
        
        for sentence in json_data["sentence"]:
            out_text.write(sentence['text']+'\n')
            
            for ne in sentence["NE"]:
                out_ne.write(ne["text"] + " " + ne["type"] + '\n')
            out_ne.write('\n')
            


out_text.close()
out_ne.close()
print("DONE, Check AIHUB_NE.txt & AIHUB_TEXT.txt")