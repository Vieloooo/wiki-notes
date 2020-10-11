wiki-notes
dev doc
 使用QT creator 进行开发.将任务分为四个组件:{
        搜索和文件管理组件:{
            1.基本的文件夹,文件名,块名 搜索
            2.单个文件文本内容的匹配搜索.
            3.文件夹,文件,的新建 删减
            4.文件的导入
        }
        富文本编辑组件:{基于qt webengine的富文本标记
            1.以'/'为功能键扩展的一系列文本标记:{
              g   1.基本的hmtl 文本tag (p h1 h2 h3 li ul )
                2.分块功能
                3.超链接{
                    1.块搜索组件
                    2.预览功能
                }
                //4.图片,多媒体
            }
           g 2.文本的导出(html md '//pdf....')
        }
        导图映射组件:{
            1.导图和文本块的可视化映射
            2.导图的删改与保存
        }
        导图管理组件:{
            1.导图的新建
            2.根据导图数量的动态导图集合显示
            
        }
    }
}

referrence{
    1.qt 5 quick intro http://c.biancheng.net/qt/
    2.qt creator example{
        1.markdown editor 
        2.qt example:{
            1.text edit
            2.markdown editor
            3.widget web engine guide
            4. html2pdf
            5.html file support md language
        }
    }
}
kanban {
    1. finish qt 5 quick intro :before 9.25
    
}

 后半期安排{

     需求:{
         文件管理部分{
          1.文件搜索功能//10.15
            1.对文件的搜索,算法难点
            2.搜索结果的显示//10.12
            3.文件名的传递 
        2.文本内部搜索//10.17
      //3.图的搜索
         }
    
        编辑部分{
            1.list功能
            2.超链接功能
                1.add local file
                2. add href
            3.文本内搜索
            4.div的生成 和id
            5.div id anchor 输入接口//10.12   之前完成
        }
        导图部分{
            1.导图的文件形式和保存,图的读取//10.12
            2.导图编辑功能优化//10.14
            3.html tag id 读取
            4.html div id anchor 信号发射10.17

        }

        整合部分{
            多个窗口类的结合
            类的mount unmount
        }

         

     }
 }