{
    'targets':[
        {
            'target_name':'jsonasync',
            'include_dirs':[
                "<!(node -e \"require('nan')\")"
            ],
            'dependencies':[
                'deps/yajl/yajl.gyp:yajl'
            ],
            'sources':['jsonasync.cc','jsonparse.cc']
        }
    ]
}
