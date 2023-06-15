// index.ts
// 获取应用实例
const app = getApp<IAppOption>()

Page({
  data: {
    show:false,
    file:{},
    num:1,
  },
  // 事件处理函数
  onLoad() {
      let that = this
      wx.offAppShow()
      wx.onAppShow(async res=>{
        console.log(res)
        if(res.scene == 1173 && res.hasOwnProperty('forwardMaterials')){//forwardMaterials 属性请详细见小程序API文档
            that.setData({ 
              file:{path:res.forwardMaterials[0].path}
            })
            that.startPrint()
        }
      })
  },
  openFileClick(){
      //处理选择本地文件
      wx.chooseMedia({count:1,mediaType:['image'],success:(res=>{
          console.log(res)
          interface obj {
            [idx: string]: any
          }
          let temp:obj = res.tempFiles[0]
          let t = res.tempFiles[0].tempFilePath.split(".")
          temp.name = '选中的图片.' + t.pop()
          this.setData({
            file:res.tempFiles[0],
            show:true
          })
      })})
  },
  chooseFileFromChat() {
    let that = this
    wx.chooseMessageFile({
      count: 1,
      type: "all", //all,video,image,file
      success:(res)=> {
        console.log(res.tempFiles[0]);
        that.setData({
          show:true,
          file:res.tempFiles[0],
        });
        console.log(that.data.file)
      },
    });
  },
  startPrint(){
      //上传temp文件并打印
      wx.showLoading({
        title:"上传文件中···"
      })
      let that = this
      console.log(this.data)

      wx.uploadFile({
        url: 'https://727rf02099.goho.co/upload', //这里需要替换为项目真实地址（做外网穿透的地址，可以用自己服务器去搭建一个流量转发）
        filePath: that.data.file.tempFilePath || that.data.file.path,
        name: 'file',
        formData: {
          'num': that.data.num
        },
        success (res){
          let r = {}
          if(typeof res.data == 'string'){
            r = JSON.parse(res.data)
          }
          if(r.code == 200){
            //将成功信息告知用户
            wx.showToast({
              icon:'success',
              title:'任务提交成功',
              success:()=>{
                // 隐藏对话框
                that.setData({
                  show:false,
                  num:1,
                })
              }
            })
            
          }
          //do something
        },fail:()=>{
            wx.showToast({
              icon:"error",
              title:"无法链接到服务器，请检查网络或联系管理员"
            })
        },complete(){
          //不管是否成功都要把loading删掉
          wx.hideLoading()
          
        }
      })
  }
})
