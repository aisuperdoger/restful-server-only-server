import time
import requests
 
# post mp4
def post_file(filename=''):
    # token = get_token()
    post_file_url = 'http://127.0.0.1:8090/api/getReturn'
    headers = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.87 Safari/537.36'
               ,'Accept-Language': 'en-US,en;q=0.9','Accept-Encoding':'gzip, deflate, br', 'token': 'token'}
    files = {"files": open(filename, 'rb')}
    post_response = requests.post(url=post_file_url,headers=headers,files=files,verify=False)
    print('post_response:{}'.format(post_response))

if __name__=="__main__":
    post_file(filename='./test.zip')