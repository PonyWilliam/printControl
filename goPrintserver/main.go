package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"

	"github.com/gin-gonic/gin"
	"golang.org/x/text/encoding/simplifiedchinese"
)

func CORSMiddleware() gin.HandlerFunc {
	return func(c *gin.Context) {
		c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
		c.Writer.Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE")
		c.Writer.Header().Set("Access-Control-Allow-Headers", "*")
		if c.Request.Method == "OPTIONS" {
			c.AbortWithStatus(204)
			return
		}
		c.Next()
	}
}
func DealFile(filename string, num string) {
	//多线程处理上传文件，控制打印
	fmt.Println(filename, num)
	cmd := exec.Command("D:\\files\\printControl.exe", filename, num)
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(err)
		return
	}

	output, err := simplifiedchinese.GB18030.NewDecoder().String(string(out)) //转换字符集，解决UTF-8乱码
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(output)
	if err != nil {
		fmt.Println(err)
	}
	//上传后1分钟删除文件
	time.Sleep(time.Minute)
	os.Remove(filename)
}

func main() {
	r := gin.Default()
	r.Use(CORSMiddleware())
	r.POST("/upload", func(ctx *gin.Context) {
		form, err := ctx.MultipartForm()

		if err != nil {
			ctx.JSON(200, gin.H{
				"code": 500,
				"msg":  "无法上传文件",
			})
		}
		files := form.File["file"]
		for _, file := range files {
			file_name := "D:\\files\\" + file.Filename
			err = ctx.SaveUploadedFile(file, file_name)
			if err != nil {
				fmt.Println(err)
			}
			go DealFile(file_name, form.Value["num"][0]) //1分钟后删除缓存文件
			// 将文件临时存储，每过一段时间自动删除
		}
		ctx.JSON(200, gin.H{
			"code": 200,
			"msg":  "文件上传完成",
		})
	})
	r.Run(":2333")
}
