function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:35,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:72,type:"fcn"};
this.def["rtX"] = {file: "DC_M_sim_c.html",line:38,type:"var"};
this.def["rtDW"] = {file: "DC_M_sim_c.html",line:41,type:"var"};
this.def["rtM_"] = {file: "DC_M_sim_c.html",line:44,type:"var"};
this.def["rtM"] = {file: "DC_M_sim_c.html",line:45,type:"var"};
this.def["rt_ertODEUpdateContinuousStates"] = {file: "DC_M_sim_c.html",line:54,type:"fcn"};
this.def["DC_M_sim_step"] = {file: "DC_M_sim_c.html",line:132,type:"fcn"};
this.def["DC_M_sim_derivatives"] = {file: "DC_M_sim_c.html",line:251,type:"fcn"};
this.def["DC_M_sim_initialize"] = {file: "DC_M_sim_c.html",line:266,type:"fcn"};
this.def["RT_MODEL"] = {file: "DC_M_sim_h.html",line:54,type:"type"};
this.def["DW"] = {file: "DC_M_sim_h.html",line:68,type:"type"};
this.def["X"] = {file: "DC_M_sim_h.html",line:74,type:"type"};
this.def["XDot"] = {file: "DC_M_sim_h.html",line:80,type:"type"};
this.def["XDis"] = {file: "DC_M_sim_h.html",line:86,type:"type"};
this.def["ODE3_IntgData"] = {file: "DC_M_sim_h.html",line:95,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["DC_M_sim_c.html"] = "../DC_M_sim.c";
	this.html2Root["DC_M_sim_c.html"] = "DC_M_sim_c.html";
	this.html2SrcPath["DC_M_sim_h.html"] = "../DC_M_sim.h";
	this.html2Root["DC_M_sim_h.html"] = "DC_M_sim_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","DC_M_sim_c.html","DC_M_sim_h.html","rtwtypes_h.html"];
