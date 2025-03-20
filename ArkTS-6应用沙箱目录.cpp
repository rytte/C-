/********************/应用沙箱目录/************************************************************/

//应用沙箱
应用沙箱是一种以安全防护为目的的隔离机制，避免数据受到恶意路径穿越访问。
在这种沙箱的保护机制下，应用可见的目录范围即为“应用沙箱目录”。


应用可以在"应用文件目录"下保存和处理自己的应用文件；
系统文件：对于应用是只读的；
用户文件：需要通过特定API同时经过用户的相应授权才能进行。


//应用文件根目录
一级目录			二级目录			三级目录			四级目录			五级目录		六级目录		七级目录
应用文件根目录	数据持久化类型	文件加密类型		分布式文件类型	应用包目录	应用子Hap名	应用子Hap内

data /
└── storage /
    ├── el1 /
    │   ├── base /
    │   │   ├── cache /
    │   │   ├── files /
    │   │   ├── preferences /
    │   │   ├── temp /
    │   │   └── haps /
    │   │       └── <module - name> /
    │   │           ├── cache /
    │   │           ├── files /
    │   │           ├── preferences /
    │   │           └── temp /
    │   ├── bundle /
    │   └── database /
    │       └── <module - name> /
    ├── el2 /
    │   ├── base /
    │   │   ├── cache /
    │   │   ├── files /
    │   │   ├── preferences /
    │   │   ├── temp /
    │   │   └── haps /
    │   │       └── <module - name> /
    │   │           ├── cache /
    │   │           ├── files /
    │   │           ├── preferences /
    │   │           └── temp /
    │   ├── distributedfiles /
    │   └── database /
    │       └── <module - name> /
    ├── el3 /
    │   ├── base /
    │   └── database /
    └── el4 /
        ├── base /
        └── database /

