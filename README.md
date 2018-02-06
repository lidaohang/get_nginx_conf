# 获取nginx配置文件格式化信息


1. 精确匹配的路径 location = /{}
(exact_match = 1 )

2. 抢占式前缀匹配的路径 location ^~ /{}
(noregex = 1)

3. 命名路径，比如location @a {}
(named = 1)


4. 普通前端匹配的路径，例如location / {}


5. 无名路径，比如if {}或者limit_except {}生成的路径
noname = 1










```
{
    "http":{
        "servers":[
            {
                "server_name":"www.baidu.com",
                "port":80,
                "locations":[
                    {
                        "location":"/index",
                        "upstream_name":"upstream_index_com",
                        "upstream_servers":"127.0.0.1:8000, 127.0.0.1:80001"
                    },
                    {
                        "location":"/home",
                        "upstream_name":"upstream_index_com",
                        "upstream_servers":"127.0.0.1:8000, 127.0.0.1:80001"
                    },
                    {
                        "location":"/test",
                        "upstream_name":"upstream_test_com",
                        "upstream_servers":"127.0.0.1:8000, 127.0.0.1:80001"
                    }
                ]
            },
            {
                "server_name":"www.qq.com",
                "port":80,
                "locations":[
                    {
                        "location":"^/orderby",
                        "upstream_name":"upstream_test_com",
                        "upstream_servers":"127.0.0.1:8000, 127.0.0.1:80001"
                    },
                    {
                        "location":"^/list",
                        "upstream_name":"upstream_test_com",
                        "upstream_servers":"127.0.0.1:8000, 127.0.0.1:80001"
                    }
                ]
            }
        ]
    }
}
```
