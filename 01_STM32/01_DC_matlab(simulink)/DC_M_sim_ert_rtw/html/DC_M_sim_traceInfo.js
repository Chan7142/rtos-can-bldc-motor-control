function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Integrator */
	this.urlHashMap["DC_M_sim:5"] = "DC_M_sim.c:149,256,299&DC_M_sim.h:58,72,78,84";
	/* <Root>/Saturation */
	this.urlHashMap["DC_M_sim:12"] = "DC_M_sim.c:195,204&DC_M_sim.h:62";
	/* <Root>/Scope */
	this.urlHashMap["DC_M_sim:2"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:2";
	/* <Root>/Scope1 */
	this.urlHashMap["DC_M_sim:4"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:4";
	/* <Root>/Transfer Fcn */
	this.urlHashMap["DC_M_sim:1"] = "DC_M_sim.c:207,259,302&DC_M_sim.h:63,73,79,85";
	/* <Root>/Unit Delay */
	this.urlHashMap["DC_M_sim:19"] = "DC_M_sim.c:155,215&DC_M_sim.h:60,65";
	/* <Root>/Unit Delay1 */
	this.urlHashMap["DC_M_sim:20"] = "DC_M_sim.c:152,212&DC_M_sim.h:59,64";
	/* <S1>/Gain */
	this.urlHashMap["DC_M_sim:10"] = "DC_M_sim.c:169";
	/* <S1>/Step */
	this.urlHashMap["DC_M_sim:11"] = "DC_M_sim.c:159,166";
	/* <S1>/Sum */
	this.urlHashMap["DC_M_sim:8"] = "DC_M_sim.c:168";
	/* <S1>/Sum1 */
	this.urlHashMap["DC_M_sim:9"] = "DC_M_sim.c:170";
	/* <S2>/Derivative Gain */
	this.urlHashMap["DC_M_sim:7:1666"] = "DC_M_sim.c:180";
	/* <S2>/Integral Gain */
	this.urlHashMap["DC_M_sim:7:1665"] = "DC_M_sim.c:175";
	/* <S2>/Integrator */
	this.urlHashMap["DC_M_sim:7:1667"] = "DC_M_sim.c:174,218&DC_M_sim.h:61,66";
	/* <S2>/Proportional Gain */
	this.urlHashMap["DC_M_sim:7:1664"] = "DC_M_sim.c:189";
	/* <S2>/Sum */
	this.urlHashMap["DC_M_sim:7:1663"] = "DC_M_sim.c:187";
	/* <S3>/DTDup */
	this.urlHashMap["DC_M_sim:7:1673"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:7:1673";
	/* <S3>/Diff */
	this.urlHashMap["DC_M_sim:7:1672"] = "DC_M_sim.c:190";
	/* <S3>/TSamp */
	this.urlHashMap["DC_M_sim:7:1670"] = "DC_M_sim.c:179,182";
	/* <S3>/UD */
	this.urlHashMap["DC_M_sim:7:1671"] = "DC_M_sim.c:188,221&DC_M_sim.h:67";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "DC_M_sim"};
	this.sidHashMap["DC_M_sim"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "DC_M_sim:13"};
	this.sidHashMap["DC_M_sim:13"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "DC_M_sim:7"};
	this.sidHashMap["DC_M_sim:7"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "DC_M_sim:7:1668"};
	this.sidHashMap["DC_M_sim:7:1668"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<Root>/Integrator"] = {sid: "DC_M_sim:5"};
	this.sidHashMap["DC_M_sim:5"] = {rtwname: "<Root>/Integrator"};
	this.rtwnameHashMap["<Root>/Saturation"] = {sid: "DC_M_sim:12"};
	this.sidHashMap["DC_M_sim:12"] = {rtwname: "<Root>/Saturation"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "DC_M_sim:2"};
	this.sidHashMap["DC_M_sim:2"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/Scope1"] = {sid: "DC_M_sim:4"};
	this.sidHashMap["DC_M_sim:4"] = {rtwname: "<Root>/Scope1"};
	this.rtwnameHashMap["<Root>/Subsystem"] = {sid: "DC_M_sim:13"};
	this.sidHashMap["DC_M_sim:13"] = {rtwname: "<Root>/Subsystem"};
	this.rtwnameHashMap["<Root>/Transfer Fcn"] = {sid: "DC_M_sim:1"};
	this.sidHashMap["DC_M_sim:1"] = {rtwname: "<Root>/Transfer Fcn"};
	this.rtwnameHashMap["<Root>/Unit Delay"] = {sid: "DC_M_sim:19"};
	this.sidHashMap["DC_M_sim:19"] = {rtwname: "<Root>/Unit Delay"};
	this.rtwnameHashMap["<Root>/Unit Delay1"] = {sid: "DC_M_sim:20"};
	this.sidHashMap["DC_M_sim:20"] = {rtwname: "<Root>/Unit Delay1"};
	this.rtwnameHashMap["<S1>/theta"] = {sid: "DC_M_sim:14"};
	this.sidHashMap["DC_M_sim:14"] = {rtwname: "<S1>/theta"};
	this.rtwnameHashMap["<S1>/speed_rad"] = {sid: "DC_M_sim:16"};
	this.sidHashMap["DC_M_sim:16"] = {rtwname: "<S1>/speed_rad"};
	this.rtwnameHashMap["<S1>/Discrete PID Controller"] = {sid: "DC_M_sim:7"};
	this.sidHashMap["DC_M_sim:7"] = {rtwname: "<S1>/Discrete PID Controller"};
	this.rtwnameHashMap["<S1>/Gain"] = {sid: "DC_M_sim:10"};
	this.sidHashMap["DC_M_sim:10"] = {rtwname: "<S1>/Gain"};
	this.rtwnameHashMap["<S1>/Step"] = {sid: "DC_M_sim:11"};
	this.sidHashMap["DC_M_sim:11"] = {rtwname: "<S1>/Step"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "DC_M_sim:8"};
	this.sidHashMap["DC_M_sim:8"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/Sum1"] = {sid: "DC_M_sim:9"};
	this.sidHashMap["DC_M_sim:9"] = {rtwname: "<S1>/Sum1"};
	this.rtwnameHashMap["<S1>/Out1"] = {sid: "DC_M_sim:15"};
	this.sidHashMap["DC_M_sim:15"] = {rtwname: "<S1>/Out1"};
	this.rtwnameHashMap["<S2>/u"] = {sid: "DC_M_sim:7:1"};
	this.sidHashMap["DC_M_sim:7:1"] = {rtwname: "<S2>/u"};
	this.rtwnameHashMap["<S2>/Derivative Gain"] = {sid: "DC_M_sim:7:1666"};
	this.sidHashMap["DC_M_sim:7:1666"] = {rtwname: "<S2>/Derivative Gain"};
	this.rtwnameHashMap["<S2>/Differentiator"] = {sid: "DC_M_sim:7:1668"};
	this.sidHashMap["DC_M_sim:7:1668"] = {rtwname: "<S2>/Differentiator"};
	this.rtwnameHashMap["<S2>/Integral Gain"] = {sid: "DC_M_sim:7:1665"};
	this.sidHashMap["DC_M_sim:7:1665"] = {rtwname: "<S2>/Integral Gain"};
	this.rtwnameHashMap["<S2>/Integrator"] = {sid: "DC_M_sim:7:1667"};
	this.sidHashMap["DC_M_sim:7:1667"] = {rtwname: "<S2>/Integrator"};
	this.rtwnameHashMap["<S2>/Proportional Gain"] = {sid: "DC_M_sim:7:1664"};
	this.sidHashMap["DC_M_sim:7:1664"] = {rtwname: "<S2>/Proportional Gain"};
	this.rtwnameHashMap["<S2>/Sum"] = {sid: "DC_M_sim:7:1663"};
	this.sidHashMap["DC_M_sim:7:1663"] = {rtwname: "<S2>/Sum"};
	this.rtwnameHashMap["<S2>/y"] = {sid: "DC_M_sim:7:10"};
	this.sidHashMap["DC_M_sim:7:10"] = {rtwname: "<S2>/y"};
	this.rtwnameHashMap["<S3>/U"] = {sid: "DC_M_sim:7:1669"};
	this.sidHashMap["DC_M_sim:7:1669"] = {rtwname: "<S3>/U"};
	this.rtwnameHashMap["<S3>/DTDup"] = {sid: "DC_M_sim:7:1673"};
	this.sidHashMap["DC_M_sim:7:1673"] = {rtwname: "<S3>/DTDup"};
	this.rtwnameHashMap["<S3>/Diff"] = {sid: "DC_M_sim:7:1672"};
	this.sidHashMap["DC_M_sim:7:1672"] = {rtwname: "<S3>/Diff"};
	this.rtwnameHashMap["<S3>/TSamp"] = {sid: "DC_M_sim:7:1670"};
	this.sidHashMap["DC_M_sim:7:1670"] = {rtwname: "<S3>/TSamp"};
	this.rtwnameHashMap["<S3>/UD"] = {sid: "DC_M_sim:7:1671"};
	this.sidHashMap["DC_M_sim:7:1671"] = {rtwname: "<S3>/UD"};
	this.rtwnameHashMap["<S3>/Y"] = {sid: "DC_M_sim:7:1674"};
	this.sidHashMap["DC_M_sim:7:1674"] = {rtwname: "<S3>/Y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
