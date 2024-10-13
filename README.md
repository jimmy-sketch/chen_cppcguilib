# 开源的命令行图形化库
本代码库旨在让开发者能够以一种简单的方式来在它们的命令行界面上放置一些简单控件，并摆脱对用Windows API等系统调用的依赖，以得到良好的跨平台效果
目前，计划有以下功能：
- [X] 单独文本的显示，更新；
- [x] 字符画的显示，更新；
- [x] 进度条的显示，更新
- [X] 对于一些排版功能的支持
- [X] 彩色字体支持
- [X] 多行文本
- [ ] 进度条自由样式切换
- [ ] 分割线……

这当前是一个WIP的项目，请不要随意clone,如要移植, 请使用releases里面公布的代码进行编译, 谢谢！
欢迎PR、star、发起issue!

## API 介绍
````mermaid 
graph LR
    subgraph utils
        string
    end
    utils --> components

    subgraph components
        direction LR
        component --> basicImage
        component --> basicProgressBar
        component --> basicText
        component --> multiLineText
        component --> singleLine
    end

    components --> page
    logicPos --> page
````
