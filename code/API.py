#-*- coding:utf-8 -*-
import urllib3
import json

# 입력 문자열은 'TEXT.txt'로 해주시면 알아서 잘라 줘요~
'''예시)
케냐
케냐 공화국 또는 케냐(Kenya)는 동아프리카의 공화국이다.
인도양에 면해 있으며 북동쪽으로 소말리아, 북쪽으로 에티오피아와 남수단, 서쪽으로 우간다, 남쪽으로 탄자니아와 국경을 맞닿고 있다.
수도는 나이로비이며 공용어는 영어와 스와힐리어이다.
케냐의 주요 종족은 키쿠유족, 루히아족, 루오족, 칼렌진족, 캄바족, 키시족,메루족 등 여러 민족으로 구성되어 있어 각각 다른 언어를 사용한다.
백인, 인도인, 아랍인 등 비아프리카계 민족은 전체 인구의 1% 정도를 차지한다.
인구는 4,403만 명(2013년 7월,CIA 추정자료)이다.
동아프리카에서 발견된 화석에 따르면 조상이 2백만 년 전 이 지역에서 살았다고 한다.
투르카나 호 근처에서의 최근 발굴에 따르면 호모 하빌리스(Homo habilis), 호모 에렉투스(Homo erectus)와 같은 호미니드인(hominid)이 260만 년 전 이 나라 땅에 있었다.
케냐의 식민 시대 역사는 1885년 독일이 잔지바르(현 탄자니아의 잔지바르 섬) 술탄의 케냐 해안 영토에 보호령을 설치한 것으로 시작되었다.
그 후 1888년 영국 동아프리카 회사가 들어왔다.
독일이 해안 영토를 1890년에 영국에게 넘겨줘 두 열강 사이의 분쟁도 적지 않았다.
1952년 10월부터 1959년 12월까지 케냐는 영국의 지배에 대한 반란(마우마우 반란)으로 비상 사태하에 있었다.
영국은 단계적으로 케냐의 독립을 허용할 수밖에 없었다.
그리하여 1957년 처음으로 아프리카인들이 피선거권을 가진 입법 회의 직접 선거를 치렀다.
그러면서 좀 더 온건한 세력에게 권력을 넘기려는 영국의 기대와는 달리 조모 케냐타(Jomo Kenyatta)가 이끄는 케냐 아프리카 국민연맹(KANU, Kenya African National Union)이 독립 정부 조직을 주도하게 되었다.
1963년 12월 12일 케냐는 독립을 선포했다.

'''
openApiURL = "http://aiopen.etri.re.kr:8000/WiseNLU"
accessKey = "여기에 엑세스 키 입력해주세요~"
analysisCode = "ner"

http_num = 0
sentence_num = 0

input_text = open("TEXT.txt", 'rt', encoding='UTF8')
out = open('API_OUT.txt', 'w', -1, "utf-8")
p_text = ""
text = input_text.readline()
	
while True:
	#print(text)
	p_text = ""
	while True:
		p_text = p_text + text + " "
		text = input_text.readline()
		
		if len(p_text + text) >= 10000 or not text:
			break

	if p_text == " ":
		break

	requestJson = {
		"access_key": accessKey,
		"argument": {
			"text": p_text,
			"analysis_code": analysisCode
		}
	}

	http = urllib3.PoolManager()
	response = http.request(
		"POST",
		openApiURL,
		headers={"Content-Type": "application/json; charset=UTF-8"},
		body=json.dumps(requestJson)
	)
	http_num += 1

	print("[responseCode] " + str(response.status))
	print("[responBody]")
	data = str(response.data, "utf-8")
	#print(data)

	json_data = json.loads(data)

	for sentence in json_data["return_object"]["sentence"]:
		sentence_num += 1
		out_text = sentence["text"]
		out_ne = ""
	
		for ne in sentence["NE"]:
			out_ne += ne["text"] + " " + ne["type"] + '\n'
		
		if out_ne != "":
			out.write(out_text + '\n' + out_ne + '\n')
		else:
			print("개체명이 없는 문장: " + out_text)

	print("http 메시지 사용 : %d" %(http_num))
	print("문장 수 : %d" %(sentence_num))

	
out.close()
print("DONE, Check API_OUT.txt")