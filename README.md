# 获取nginx配置文件格式化信息

```
{
    "http":{
        "servers":[
            {
                "server_name":"www.didichuxing.com",
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
                "server_name":"www.udache.com",
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
