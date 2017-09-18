static ngx_str_t                    HTTP_KEY = "http"
static ngx_str_t                    SERVERS_KEY = "servers"
static ngx_str_t                    SERVER_NAME_KEY = "server_name";
static ngx_str_t                    SERVER_PORT_KEY = "server_port";
static ngx_str_t                    LOCATIONS_KEY = "locations";
static ngx_str_t                    LOCATION_KEY = "location";



static void
ngx_http_didi_conf_get_static_locations(yajl_gen &g, ngx_http_location_tree_node_t *node)
{
    
    if ( node == NULL ) {
        return;
    }

    yajl_gen_string(g, (unsigned char *) LOCATION_KEY.data, LOCATION_KEY.len);
    yajl_gen_string(g, (unsigned char *)node->name, node->len);


    if ( node->left ) {
        return ngx_http_get_test_locations(r,node->left);
    }

    if ( node->right ) {
        return ngx_http_get_test_locations(r,node->right);
    }

}


static void
ngx_http_didi_conf_get_regex_locations(yajl_gen &g, ngx_http_core_loc_conf_t **clcfp)
{

    if ( clcfp ) {
        return;
    }

    for (clcfp = clcf->regex_locations; *clcfp; clcfp++) {

        yajl_gen_string(g, (unsigned char *) LOCATION_KEY.data, LOCATION_KEY.len);
        yajl_gen_string(g, (unsigned char *)(*clcfp)->name.data (*clcfp)->name.len);                
    }

}

/*
{
    "http":{
        "servers":[
            {
                "server_name":"www.didichuxing.com",
                "port":80,
                "locations":[
                    {
                        "location":"/index"
                    },
                    {
                        "location":"/home"
                    }
                ]
            }
        ]
    }
}
*/


static ngx_int_t
ngx_http_didi_conf_get(lua_State *L)
{
    size_t                                      s, i, j, n;
    size_t                                      len;
    ngx_http_conf_addr_t                        *addr;
    ngx_http_conf_port_t                        *port;
    const unsigned char                         *buf;
    ngx_http_request_t                          *r;
    ngx_http_core_main_conf_t                   *cmcf;
    ngx_http_core_loc_conf_t                    *clcf;
    ngx_http_core_srv_conf_t                    **server;
    ngx_http_server_name_t                      *name;
    yajl_gen                                    g;
    yajl_val                                    node;
    yajl_gen_status                             status;



    g = yajl_gen_alloc(NULL);
    if ( g == NULL ) {
        return NGX_ERROR;
    }

    yajl_gen_config(g, yajl_gen_beautify, 0);

    yajl_gen_map_open(g);

    //http
    yajl_gen_string(g, (unsigned char *)HTTP_KEY.data, HTTP_KEY.len);


    yajl_gen_map_open(g);

    //servers
    yajl_gen_string(g, (unsigned char *)SERVERS_KEY.data, SERVERS_KEY.len);


    yajl_gen_array_open(g);


    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    port = cmcf->ports->elts;
    for (s = 0; s < cmcf->ports->nelts; s++) {

        addr = port[s].addrs.elts;
        for (i = 0; i < port[s].addrs.nelts; i++) {

            

            server = addr[i].servers.elts;
            for (j = 0; j < addr[i].servers.nelts; j++) {

                yajl_gen_map_open(g);

                name = server[j]->server_names.elts;

                for (n = 0; n < server[j]->server_names.nelts; n++) {

                    //server_name
                    yajl_gen_string(g, (unsigned char *)SERVER_NAME_KEY.data, SERVER_NAME_KEY.len);
                    yajl_gen_string(g, (unsigned char *)name[n].name.data, name[n].name.len);

                    //server_port
                    yajl_gen_string(g, (unsigned char *) SERVER_PORT_KEY.data, SERVER_PORT_KEY.len);
                    yajl_gen_string(g, (unsigned char *) addr[i].opt.addr, ngx_len(addr[i].opt.addr));
                }

                clcf = server[j]->ctx->loc_conf[ngx_http_core_module.ctx_index];

                yajl_gen_string(g, (char *) LOCATIONS_KEY.data, LOCATIONS_KEY.len);
                
                yajl_gen_array_open(g);

                ngx_http_didi_conf_get_static_locations(g, clcf->static_locations);

                ngx_http_didi_conf_get_regex_locations(g, clcf->regex_locations);

                yajl_gen_array_close(g);

                yajl_gen_map_close(g);
            }
            
        }
    }

    yajl_gen_array_close(g);

    yajl_gen_map_close(g);

    yajl_gen_map_close(g);

    status = yajl_gen_get_buf(g, &buf, &len);
    if(status != yajl_gen_status_ok) {
        yajl_gen_free(g);
        lua_pushlstring(L);

        return 1;
    }

    lua_pushlstring(L, (char *) buf, len);

    return 1;
}
