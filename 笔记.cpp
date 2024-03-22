


git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890


git config --global - l


git config --global --unset http.proxy
git config --global --unset https.proxy




[
{
	"tripNum":1,
	"trainTypeCn" : "普通车",
	"trainTypeEn" : "Local",
	"curStationName":"深大",
	"curStationNameEn":"SZU",
	"arriveTime" : 10,
	"unitCn" : "分",
	"unitEn" : "min",
	"destStationName":"上海",
	"destStationNameEn":"ShangHai",
	"holdStatus" : 1,
	"holdStatusCn" : "扣车",
	"holdStatusEn" : "holdStatus",
	"crowdings" : [0, 1, 0, 2] ,
	"temperature" : [0, 1, 0, 2]
},
{
	"tripNum":2,
	"trainTypeCn" : "普通车",
	"trainTypeEn" : "Local",
	"arriveTime" : 10,
	"unitCn" : "分",
	"unitEn" : "min",
	"destStationName" : "北京",
	"destStationNameEn" : "BeiJing"
},
{
	"tripNum":3,
	"trainTypeCn" : "普通车",
	"trainTypeEn" : "Local",
	"arriveTime" : 10,
	"unitCn" : "分",
	"unitEn" : "min",
	"destStationName" : "深圳",
	"destStationNameEn" : "ShangHai"
}
]



"holdStatus" : 1,
"holdStatusCn" : "扣车",
"holdStatusEn" : "holdStatus",

"stableStatus" : 1,
"stableStatusCn" : "停稳",
"stableStatusEn" : "stableStatus"

"blockStatus" : 1,
"blockStatusCn" : "阻塞",
"blockStatusEn" : "blockStatus",

"skinStatus" : 1,
"skinStatusCn" : "本次列车通过不停车",
"skinStatusEn" : "The train will not stop at this station",

"serviceStatus" : 1,
"serviceStatusCn" : "清客",
"serviceStatusEn" : "serviceStatus",

