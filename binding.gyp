{
    'targets':[
        {
            'target_name':'asyncparser',
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
