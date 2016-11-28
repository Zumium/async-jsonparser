{
    'targets':[
        {
            'target_name':'async-jsonparser',
            'include_dirs':[
                "<!(node -e \"require('nan')\")"
            ],
            'dependencies':[
                'deps/yajl/yajl.gyp:yajl'
            ],
            'sources':['main.cc','jsonparse.cc']
        }
    ]
}
