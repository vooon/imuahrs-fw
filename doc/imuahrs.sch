<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="elem">
<packages>
<package name="LGA7">
<description>&lt;b&gt;8-Terminal Ceramic Leadless Chip Carrier [LCC] (E-8)&lt;/b&gt;&lt;p&gt;
Source: www.analog.com/UploadedFiles/Packages/189346426E_8.pdf</description>
<wire x1="-2.4" y1="2.2" x2="-2.4" y2="1.5" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="1.05" x2="-2.4" y2="0.2" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-0.2" x2="-2.4" y2="-1.05" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-1.5" x2="-2.4" y2="-2.2" width="0.2032" layer="51"/>
<wire x1="-2.2" y1="-2.4" x2="-0.2" y2="-2.4" width="0.2032" layer="51"/>
<wire x1="0.2" y1="-2.4" x2="2.2" y2="-2.4" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-2.2" x2="2.4" y2="-1.5" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.05" x2="2.4" y2="-0.2" width="0.2032" layer="51"/>
<wire x1="2.4" y1="0.2" x2="2.4" y2="1.05" width="0.2032" layer="51"/>
<wire x1="2.4" y1="1.5" x2="2.4" y2="2.2" width="0.2032" layer="51"/>
<wire x1="2.2" y1="2.4" x2="0.2" y2="2.4" width="0.2032" layer="51"/>
<wire x1="-0.2" y1="2.4" x2="-2.2" y2="2.4" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="1.5" x2="-2.4" y2="1.05" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.4" y1="0.2" x2="-2.4" y2="-0.2" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.4" y1="-1.05" x2="-2.4" y2="-1.5" width="0.2032" layer="51" curve="-180"/>
<wire x1="-0.2" y1="-2.4" x2="0.2" y2="-2.4" width="0.2032" layer="51" curve="-180"/>
<wire x1="2.4" y1="-1.5" x2="2.4" y2="-1.05" width="0.2032" layer="51" curve="-180"/>
<wire x1="2.4" y1="-0.2" x2="2.4" y2="0.2" width="0.2032" layer="51" curve="-180"/>
<wire x1="2.4" y1="1.05" x2="2.4" y2="1.5" width="0.2032" layer="51" curve="-180"/>
<wire x1="0.2" y1="2.4" x2="-0.2" y2="2.4" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.4" y1="2.2" x2="-2.2" y2="2.4" width="0.2032" layer="21" curve="77.319617"/>
<wire x1="2.2" y1="2.4" x2="2.4" y2="2.2" width="0.2032" layer="21" curve="77.319617"/>
<wire x1="2.4" y1="-2.2" x2="2.2" y2="-2.4" width="0.2032" layer="21" curve="77.319617"/>
<wire x1="-2.2" y1="-2.4" x2="-2.4" y2="-2.2" width="0.2032" layer="21" curve="77.319617"/>
<wire x1="-2.4" y1="2.2" x2="-2.4" y2="1.95" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="2.4" x2="-0.65" y2="2.4" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-1.95" x2="-2.4" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="-2.4" x2="-0.75" y2="-2.4" width="0.2032" layer="21"/>
<wire x1="0.7" y1="-2.4" x2="2.2" y2="-2.4" width="0.2032" layer="21"/>
<wire x1="2.4" y1="-2.2" x2="2.4" y2="-1.95" width="0.2032" layer="21"/>
<wire x1="2.4" y1="1.95" x2="2.4" y2="2.2" width="0.2032" layer="21"/>
<wire x1="2.2" y1="2.4" x2="0.65" y2="2.4" width="0.2032" layer="21"/>
<circle x="0" y="0.6" radius="0.25" width="0" layer="21"/>
<smd name="1" x="-1.8669" y="1.27" dx="1.5" dy="0.7" layer="1"/>
<smd name="2" x="-1.8669" y="0" dx="1.5" dy="0.7" layer="1"/>
<smd name="3" x="-1.8669" y="-1.27" dx="1.5" dy="0.7" layer="1"/>
<smd name="4" x="1.8669" y="-1.27" dx="1.5" dy="0.7" layer="1" rot="R180"/>
<smd name="5" x="1.8669" y="0" dx="1.5" dy="0.7" layer="1" rot="R180"/>
<smd name="6" x="1.8669" y="1.27" dx="1.5" dy="0.7" layer="1" rot="R180"/>
<smd name="7" x="0" y="1.8669" dx="1.5" dy="0.7" layer="1" rot="R270"/>
<text x="-2.54" y="3.048" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-4.064" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="PLS04">
<pad name="1" x="0" y="3.81" drill="0.8" shape="square"/>
<pad name="2" x="0" y="1.27" drill="0.8"/>
<pad name="3" x="0" y="-1.27" drill="0.8"/>
<pad name="4" x="0" y="-3.81" drill="0.8"/>
</package>
<package name="QFN16-4X4">
<description>&lt;b&gt;16-Lead Plastic Quad Flat, No Lead Package (ML) - 4x4x0.9mm Body [QFN]&lt;/b&gt;&lt;p&gt;
Source: http://ww1.microchip.com/downloads/en/DeviceDoc/41203E.pdf</description>
<wire x1="-1.95" y1="1.925" x2="1.95" y2="1.925" width="0.1016" layer="21"/>
<wire x1="1.95" y1="-1.95" x2="-1.95" y2="-1.95" width="0.1016" layer="21"/>
<wire x1="-1.95" y1="1.925" x2="-1.95" y2="-1.95" width="0.1016" layer="51"/>
<wire x1="1.95" y1="-1.95" x2="1.95" y2="1.925" width="0.1016" layer="51"/>
<smd name="1" x="-2" y="0.975" dx="0.8" dy="0.35" layer="1" stop="no" cream="no"/>
<smd name="2" x="-2" y="0.325" dx="0.8" dy="0.35" layer="1" stop="no" cream="no"/>
<smd name="3" x="-2" y="-0.325" dx="0.8" dy="0.35" layer="1" stop="no" cream="no"/>
<smd name="4" x="-2" y="-0.975" dx="0.8" dy="0.35" layer="1" stop="no" cream="no"/>
<smd name="EXP" x="0" y="0" dx="2.5" dy="2.5" layer="1" stop="no" cream="no"/>
<smd name="5" x="-0.975" y="-2" dx="0.8" dy="0.35" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="6" x="-0.325" y="-2" dx="0.8" dy="0.35" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="7" x="0.325" y="-2" dx="0.8" dy="0.35" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="8" x="0.975" y="-2" dx="0.8" dy="0.35" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="9" x="2" y="-0.975" dx="0.8" dy="0.35" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="10" x="2" y="-0.325" dx="0.8" dy="0.35" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="11" x="2" y="0.325" dx="0.8" dy="0.35" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="12" x="2" y="0.975" dx="0.8" dy="0.35" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="13" x="0.975" y="2" dx="0.8" dy="0.35" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="14" x="0.325" y="2" dx="0.8" dy="0.35" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="15" x="-0.325" y="2" dx="0.8" dy="0.35" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="16" x="-0.975" y="2" dx="0.8" dy="0.35" layer="1" rot="R270" stop="no" cream="no"/>
<text x="-1.95" y="2.6" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.95" y="-3.9" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.95" y1="1.475" x2="-1.525" y2="1.925" layer="51"/>
<rectangle x1="-1.3" y1="-1.3" x2="1.3" y2="1.3" layer="29"/>
<rectangle x1="-1.175" y1="-1.175" x2="1.175" y2="1.175" layer="31"/>
<rectangle x1="-2.45" y1="0.75" x2="-1.55" y2="1.2" layer="29"/>
<rectangle x1="-2.375" y1="0.825" x2="-1.625" y2="1.125" layer="31"/>
<rectangle x1="-2.45" y1="0.1" x2="-1.55" y2="0.55" layer="29"/>
<rectangle x1="-2.375" y1="0.175" x2="-1.625" y2="0.475" layer="31"/>
<rectangle x1="-2.45" y1="-0.55" x2="-1.55" y2="-0.1" layer="29"/>
<rectangle x1="-2.375" y1="-0.475" x2="-1.625" y2="-0.175" layer="31"/>
<rectangle x1="-2.45" y1="-1.2" x2="-1.55" y2="-0.75" layer="29"/>
<rectangle x1="-2.375" y1="-1.125" x2="-1.625" y2="-0.825" layer="31"/>
<rectangle x1="-1.425" y1="-2.225" x2="-0.525" y2="-1.775" layer="29" rot="R90"/>
<rectangle x1="-1.35" y1="-2.15" x2="-0.6" y2="-1.85" layer="31" rot="R90"/>
<rectangle x1="-0.775" y1="-2.225" x2="0.125" y2="-1.775" layer="29" rot="R90"/>
<rectangle x1="-0.7" y1="-2.15" x2="0.05" y2="-1.85" layer="31" rot="R90"/>
<rectangle x1="-0.125" y1="-2.225" x2="0.775" y2="-1.775" layer="29" rot="R90"/>
<rectangle x1="-0.05" y1="-2.15" x2="0.7" y2="-1.85" layer="31" rot="R90"/>
<rectangle x1="0.525" y1="-2.225" x2="1.425" y2="-1.775" layer="29" rot="R90"/>
<rectangle x1="0.6" y1="-2.15" x2="1.35" y2="-1.85" layer="31" rot="R90"/>
<rectangle x1="1.55" y1="-1.2" x2="2.45" y2="-0.75" layer="29" rot="R180"/>
<rectangle x1="1.625" y1="-1.125" x2="2.375" y2="-0.825" layer="31" rot="R180"/>
<rectangle x1="1.55" y1="-0.55" x2="2.45" y2="-0.1" layer="29" rot="R180"/>
<rectangle x1="1.625" y1="-0.475" x2="2.375" y2="-0.175" layer="31" rot="R180"/>
<rectangle x1="1.55" y1="0.1" x2="2.45" y2="0.55" layer="29" rot="R180"/>
<rectangle x1="1.625" y1="0.175" x2="2.375" y2="0.475" layer="31" rot="R180"/>
<rectangle x1="1.55" y1="0.75" x2="2.45" y2="1.2" layer="29" rot="R180"/>
<rectangle x1="1.625" y1="0.825" x2="2.375" y2="1.125" layer="31" rot="R180"/>
<rectangle x1="0.525" y1="1.775" x2="1.425" y2="2.225" layer="29" rot="R270"/>
<rectangle x1="0.6" y1="1.85" x2="1.35" y2="2.15" layer="31" rot="R270"/>
<rectangle x1="-0.125" y1="1.775" x2="0.775" y2="2.225" layer="29" rot="R270"/>
<rectangle x1="-0.05" y1="1.85" x2="0.7" y2="2.15" layer="31" rot="R270"/>
<rectangle x1="-0.775" y1="1.775" x2="0.125" y2="2.225" layer="29" rot="R270"/>
<rectangle x1="-0.7" y1="1.85" x2="0.05" y2="2.15" layer="31" rot="R270"/>
<rectangle x1="-1.425" y1="1.775" x2="-0.525" y2="2.225" layer="29" rot="R270"/>
<rectangle x1="-1.35" y1="1.85" x2="-0.6" y2="2.15" layer="31" rot="R270"/>
</package>
<package name="PLS05">
<pad name="1" x="0" y="5.08" drill="0.8" shape="square"/>
<pad name="2" x="0" y="2.54" drill="0.8"/>
<pad name="3" x="0" y="0" drill="0.8"/>
<pad name="4" x="0" y="-2.54" drill="0.8"/>
<pad name="5" x="0" y="-5.08" drill="0.8"/>
</package>
<package name="QFN24-4X4">
<description>&lt;b&gt;UF Package 24-Lead (4mm × 4mm) Plastic QFN&lt;/b&gt;&lt;p&gt;
Source: http://cds.linear.com/docs/Datasheet/5598f.pdf</description>
<wire x1="-1.9" y1="-1.9" x2="1.9" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="1.9" y1="-1.9" x2="1.9" y2="1.9" width="0.2032" layer="51"/>
<wire x1="1.9" y1="1.9" x2="-1.9" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-1.9" y1="1.9" x2="-1.9" y2="-1.9" width="0.2032" layer="51"/>
<circle x="-1.345" y="1.345" radius="0.155" width="0" layer="51"/>
<smd name="1" x="-1.9" y="1.25" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="2" x="-1.9" y="0.75" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="3" x="-1.9" y="0.25" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="4" x="-1.9" y="-0.25" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="5" x="-1.9" y="-0.75" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="6" x="-1.9" y="-1.25" dx="0.7" dy="0.25" layer="1" stop="no" cream="no"/>
<smd name="7" x="-1.25" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="8" x="-0.75" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="9" x="-0.25" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="10" x="0.25" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="11" x="0.75" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="12" x="1.25" y="-1.9" dx="0.7" dy="0.25" layer="1" rot="R90" stop="no" cream="no"/>
<smd name="13" x="1.9" y="-1.25" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="14" x="1.9" y="-0.75" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="15" x="1.9" y="-0.25" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="16" x="1.9" y="0.25" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="17" x="1.9" y="0.75" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="18" x="1.9" y="1.25" dx="0.7" dy="0.25" layer="1" rot="R180" stop="no" cream="no"/>
<smd name="19" x="1.25" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="20" x="0.75" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="21" x="0.25" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="22" x="-0.25" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="23" x="-0.75" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="24" x="-1.25" y="1.9" dx="0.7" dy="0.25" layer="1" rot="R270" stop="no" cream="no"/>
<smd name="EXP" x="0" y="0" dx="2.45" dy="2.45" layer="1" stop="no" cream="no"/>
<text x="-2" y="2.5" size="1.27" layer="25">&gt;NAME</text>
<text x="-2" y="-3.75" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.275" y1="1.1" x2="-1.525" y2="1.4" layer="29"/>
<rectangle x1="-2.2" y1="1.15" x2="-1.575" y2="1.35" layer="31"/>
<rectangle x1="-2.275" y1="0.6" x2="-1.525" y2="0.9" layer="29"/>
<rectangle x1="-2.2" y1="0.65" x2="-1.575" y2="0.85" layer="31"/>
<rectangle x1="-2.275" y1="0.1" x2="-1.525" y2="0.4" layer="29"/>
<rectangle x1="-2.2" y1="0.15" x2="-1.575" y2="0.35" layer="31"/>
<rectangle x1="-2.275" y1="-0.4" x2="-1.525" y2="-0.1" layer="29"/>
<rectangle x1="-2.2" y1="-0.35" x2="-1.575" y2="-0.15" layer="31"/>
<rectangle x1="-2.275" y1="-0.9" x2="-1.525" y2="-0.6" layer="29"/>
<rectangle x1="-2.2" y1="-0.85" x2="-1.575" y2="-0.65" layer="31"/>
<rectangle x1="-2.275" y1="-1.4" x2="-1.525" y2="-1.1" layer="29"/>
<rectangle x1="-2.2" y1="-1.35" x2="-1.575" y2="-1.15" layer="31"/>
<rectangle x1="-1.625" y1="-2.05" x2="-0.875" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="-1.5625" y1="-1.9875" x2="-0.9375" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="-1.125" y1="-2.05" x2="-0.375" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="-1.0625" y1="-1.9875" x2="-0.4375" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="-0.625" y1="-2.05" x2="0.125" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="-0.5625" y1="-1.9875" x2="0.0625" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="-0.125" y1="-2.05" x2="0.625" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="-0.0625" y1="-1.9875" x2="0.5625" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="0.375" y1="-2.05" x2="1.125" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="0.4375" y1="-1.9875" x2="1.0625" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="0.875" y1="-2.05" x2="1.625" y2="-1.75" layer="29" rot="R90"/>
<rectangle x1="0.9375" y1="-1.9875" x2="1.5625" y2="-1.7875" layer="31" rot="R90"/>
<rectangle x1="1.525" y1="-1.4" x2="2.275" y2="-1.1" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="-1.35" x2="2.2" y2="-1.15" layer="31" rot="R180"/>
<rectangle x1="1.525" y1="-0.9" x2="2.275" y2="-0.6" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="-0.85" x2="2.2" y2="-0.65" layer="31" rot="R180"/>
<rectangle x1="1.525" y1="-0.4" x2="2.275" y2="-0.1" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="-0.35" x2="2.2" y2="-0.15" layer="31" rot="R180"/>
<rectangle x1="1.525" y1="0.1" x2="2.275" y2="0.4" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="0.15" x2="2.2" y2="0.35" layer="31" rot="R180"/>
<rectangle x1="1.525" y1="0.6" x2="2.275" y2="0.9" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="0.65" x2="2.2" y2="0.85" layer="31" rot="R180"/>
<rectangle x1="1.525" y1="1.1" x2="2.275" y2="1.4" layer="29" rot="R180"/>
<rectangle x1="1.575" y1="1.15" x2="2.2" y2="1.35" layer="31" rot="R180"/>
<rectangle x1="0.875" y1="1.75" x2="1.625" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="0.9375" y1="1.7875" x2="1.5625" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="0.375" y1="1.75" x2="1.125" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="0.4375" y1="1.7875" x2="1.0625" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="-0.125" y1="1.75" x2="0.625" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="-0.0625" y1="1.7875" x2="0.5625" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="-0.625" y1="1.75" x2="0.125" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="-0.5625" y1="1.7875" x2="0.0625" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="-1.125" y1="1.75" x2="-0.375" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="-1.0625" y1="1.7875" x2="-0.4375" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="-1.625" y1="1.75" x2="-0.875" y2="2.05" layer="29" rot="R270"/>
<rectangle x1="-1.5625" y1="1.7875" x2="-0.9375" y2="1.9875" layer="31" rot="R270"/>
<rectangle x1="-1.95" y1="1.525" x2="-1.525" y2="1.975" layer="21"/>
<polygon width="0.2032" layer="29">
<vertex x="-1.175" y="1.175"/>
<vertex x="0.975" y="1.175" curve="90.10195"/>
<vertex x="1.175" y="0.95"/>
<vertex x="1.175" y="-1.175"/>
<vertex x="-1.175" y="-1.175"/>
</polygon>
<polygon width="0.2032" layer="31">
<vertex x="-1" y="1"/>
<vertex x="1" y="1"/>
<vertex x="1" y="-1"/>
<vertex x="-1" y="-1"/>
</polygon>
</package>
<package name="QFN36">
<description>&lt;b&gt;QFN 32&lt;/b&gt; 5 x 5 mm&lt;p&gt;
Source: http://datasheets.maxim-ic.com/en/ds/MAX7042.pdf</description>
<wire x1="-2.45" y1="2.45" x2="2.95" y2="2.45" width="0.1016" layer="51"/>
<wire x1="2.95" y1="2.45" x2="2.95" y2="-2.95" width="0.1016" layer="51"/>
<wire x1="2.95" y1="-2.95" x2="-2.45" y2="-2.95" width="0.1016" layer="51"/>
<wire x1="-2.45" y1="-2.95" x2="-2.45" y2="2.45" width="0.1016" layer="51"/>
<wire x1="-2.45" y1="2.05" x2="-2.45" y2="2.45" width="0.1016" layer="21"/>
<wire x1="-2.45" y1="2.45" x2="-2.05" y2="2.45" width="0.1016" layer="21"/>
<wire x1="2.55" y1="2.45" x2="2.95" y2="2.45" width="0.1016" layer="21"/>
<wire x1="2.95" y1="2.45" x2="2.95" y2="2.05" width="0.1016" layer="21"/>
<wire x1="2.95" y1="-2.55" x2="2.95" y2="-2.95" width="0.1016" layer="21"/>
<wire x1="2.95" y1="-2.95" x2="2.55" y2="-2.95" width="0.1016" layer="21"/>
<wire x1="-2.05" y1="-2.95" x2="-2.45" y2="-2.95" width="0.1016" layer="21"/>
<wire x1="-2.45" y1="-2.95" x2="-2.45" y2="-2.55" width="0.1016" layer="21"/>
<circle x="-2.175" y="2.175" radius="0.15" width="0" layer="21"/>
<smd name="EXP" x="0.25" y="-0.25" dx="3.7" dy="3.7" layer="1" roundness="20" stop="no" cream="no"/>
<smd name="1" x="-2.3" y="1.75" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="2" x="-2.3" y="1.25" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="3" x="-2.3" y="0.75" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="4" x="-2.3" y="0.25" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="5" x="-2.3" y="-0.25" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="6" x="-2.3" y="-0.75" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="7" x="-2.3" y="-1.25" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="8" x="-2.3" y="-1.75" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="10" x="-1.75" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="11" x="-1.25" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="12" x="-0.75" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="13" x="-0.25" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="14" x="0.25" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="15" x="0.75" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="16" x="1.25" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="17" x="1.75" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="20" x="2.8" y="-1.75" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="21" x="2.8" y="-1.25" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="22" x="2.8" y="-0.75" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="23" x="2.8" y="-0.25" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="24" x="2.8" y="0.25" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="25" x="2.8" y="0.75" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="26" x="2.8" y="1.25" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="27" x="2.8" y="1.75" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="29" x="1.75" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="30" x="1.25" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="31" x="0.75" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="32" x="0.25" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="33" x="-0.25" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="34" x="-0.75" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="35" x="-1.25" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<smd name="36" x="-1.75" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
<text x="-4.05" y="-5.35" size="1.27" layer="27">&gt;VALUE</text>
<text x="-3.8" y="3.25" size="1.27" layer="25">&gt;NAME</text>
<rectangle x1="-0.3" y1="1.1" x2="0.3" y2="1.4" layer="31"/>
<rectangle x1="-0.3" y1="0.6" x2="0.3" y2="0.9" layer="31"/>
<rectangle x1="-0.3" y1="0.1" x2="0.3" y2="0.4" layer="31"/>
<rectangle x1="-0.3" y1="-0.4" x2="0.3" y2="-0.1" layer="31"/>
<rectangle x1="-0.3" y1="-0.9" x2="0.3" y2="-0.6" layer="31"/>
<rectangle x1="-0.3" y1="-1.4" x2="0.3" y2="-1.1" layer="31"/>
<rectangle x1="-1.3" y1="1.1" x2="-0.7" y2="1.4" layer="31"/>
<rectangle x1="-1.3" y1="0.6" x2="-0.7" y2="0.9" layer="31"/>
<rectangle x1="-1.3" y1="0.1" x2="-0.7" y2="0.4" layer="31"/>
<rectangle x1="-1.3" y1="-0.4" x2="-0.7" y2="-0.1" layer="31"/>
<rectangle x1="-1.3" y1="-0.9" x2="-0.7" y2="-0.6" layer="31"/>
<rectangle x1="-1.3" y1="-1.4" x2="-0.7" y2="-1.1" layer="31"/>
<rectangle x1="0.7" y1="1.1" x2="1.3" y2="1.4" layer="31"/>
<rectangle x1="0.7" y1="0.6" x2="1.3" y2="0.9" layer="31"/>
<rectangle x1="0.7" y1="0.1" x2="1.3" y2="0.4" layer="31"/>
<rectangle x1="0.7" y1="-0.4" x2="1.3" y2="-0.1" layer="31"/>
<rectangle x1="0.7" y1="-0.9" x2="1.3" y2="-0.6" layer="31"/>
<rectangle x1="0.7" y1="-1.4" x2="1.3" y2="-1.1" layer="31"/>
<polygon width="0.5" layer="29">
<vertex x="-1.325" y="1.175"/>
<vertex x="-1.175" y="1.325"/>
<vertex x="1.325" y="1.325"/>
<vertex x="1.325" y="-1.325"/>
<vertex x="-1.325" y="-1.325"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="1.85"/>
<vertex x="-2.1" y="1.85"/>
<vertex x="-2.05" y="1.8"/>
<vertex x="-2.05" y="1.65"/>
<vertex x="-2.55" y="1.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="1.825"/>
<vertex x="-2.125" y="1.825"/>
<vertex x="-2.075" y="1.775"/>
<vertex x="-2.075" y="1.675"/>
<vertex x="-2.525" y="1.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="1.35"/>
<vertex x="-2.05" y="1.35"/>
<vertex x="-2.05" y="1.15"/>
<vertex x="-2.55" y="1.15"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="1.325"/>
<vertex x="-2.075" y="1.325"/>
<vertex x="-2.075" y="1.175"/>
<vertex x="-2.525" y="1.175"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="0.85"/>
<vertex x="-2.05" y="0.85"/>
<vertex x="-2.05" y="0.65"/>
<vertex x="-2.55" y="0.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="0.825"/>
<vertex x="-2.075" y="0.825"/>
<vertex x="-2.075" y="0.675"/>
<vertex x="-2.525" y="0.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="0.35"/>
<vertex x="-2.05" y="0.35"/>
<vertex x="-2.05" y="0.15"/>
<vertex x="-2.55" y="0.15"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="0.325"/>
<vertex x="-2.075" y="0.325"/>
<vertex x="-2.075" y="0.175"/>
<vertex x="-2.525" y="0.175"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="-0.15"/>
<vertex x="-2.05" y="-0.15"/>
<vertex x="-2.05" y="-0.35"/>
<vertex x="-2.55" y="-0.35"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="-0.175"/>
<vertex x="-2.075" y="-0.175"/>
<vertex x="-2.075" y="-0.325"/>
<vertex x="-2.525" y="-0.325"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="-0.65"/>
<vertex x="-2.05" y="-0.65"/>
<vertex x="-2.05" y="-0.85"/>
<vertex x="-2.55" y="-0.85"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="-0.675"/>
<vertex x="-2.075" y="-0.675"/>
<vertex x="-2.075" y="-0.825"/>
<vertex x="-2.525" y="-0.825"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="-1.15"/>
<vertex x="-2.05" y="-1.15"/>
<vertex x="-2.05" y="-1.35"/>
<vertex x="-2.55" y="-1.35"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="-1.175"/>
<vertex x="-2.075" y="-1.175"/>
<vertex x="-2.075" y="-1.325"/>
<vertex x="-2.525" y="-1.325"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-2.55" y="-1.85"/>
<vertex x="-2.1" y="-1.85"/>
<vertex x="-2.05" y="-1.8"/>
<vertex x="-2.05" y="-1.65"/>
<vertex x="-2.55" y="-1.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-2.525" y="-1.825"/>
<vertex x="-2.125" y="-1.825"/>
<vertex x="-2.075" y="-1.775"/>
<vertex x="-2.075" y="-1.675"/>
<vertex x="-2.525" y="-1.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-1.85" y="-2.55"/>
<vertex x="-1.85" y="-2.1"/>
<vertex x="-1.8" y="-2.05"/>
<vertex x="-1.65" y="-2.05"/>
<vertex x="-1.65" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-1.825" y="-2.525"/>
<vertex x="-1.825" y="-2.125"/>
<vertex x="-1.775" y="-2.075"/>
<vertex x="-1.675" y="-2.075"/>
<vertex x="-1.675" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-1.35" y="-2.55"/>
<vertex x="-1.35" y="-2.05"/>
<vertex x="-1.15" y="-2.05"/>
<vertex x="-1.15" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-1.325" y="-2.525"/>
<vertex x="-1.325" y="-2.075"/>
<vertex x="-1.175" y="-2.075"/>
<vertex x="-1.175" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-0.85" y="-2.55"/>
<vertex x="-0.85" y="-2.05"/>
<vertex x="-0.65" y="-2.05"/>
<vertex x="-0.65" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-0.825" y="-2.525"/>
<vertex x="-0.825" y="-2.075"/>
<vertex x="-0.675" y="-2.075"/>
<vertex x="-0.675" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-0.35" y="-2.55"/>
<vertex x="-0.35" y="-2.05"/>
<vertex x="-0.15" y="-2.05"/>
<vertex x="-0.15" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-0.325" y="-2.525"/>
<vertex x="-0.325" y="-2.075"/>
<vertex x="-0.175" y="-2.075"/>
<vertex x="-0.175" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="0.15" y="-2.55"/>
<vertex x="0.15" y="-2.05"/>
<vertex x="0.35" y="-2.05"/>
<vertex x="0.35" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="0.175" y="-2.525"/>
<vertex x="0.175" y="-2.075"/>
<vertex x="0.325" y="-2.075"/>
<vertex x="0.325" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="0.65" y="-2.55"/>
<vertex x="0.65" y="-2.05"/>
<vertex x="0.85" y="-2.05"/>
<vertex x="0.85" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="0.675" y="-2.525"/>
<vertex x="0.675" y="-2.075"/>
<vertex x="0.825" y="-2.075"/>
<vertex x="0.825" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="1.15" y="-2.55"/>
<vertex x="1.15" y="-2.05"/>
<vertex x="1.35" y="-2.05"/>
<vertex x="1.35" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="1.175" y="-2.525"/>
<vertex x="1.175" y="-2.075"/>
<vertex x="1.325" y="-2.075"/>
<vertex x="1.325" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="1.85" y="-2.55"/>
<vertex x="1.85" y="-2.1"/>
<vertex x="1.8" y="-2.05"/>
<vertex x="1.65" y="-2.05"/>
<vertex x="1.65" y="-2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="1.825" y="-2.525"/>
<vertex x="1.825" y="-2.125"/>
<vertex x="1.775" y="-2.075"/>
<vertex x="1.675" y="-2.075"/>
<vertex x="1.675" y="-2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="-1.85"/>
<vertex x="2.1" y="-1.85"/>
<vertex x="2.05" y="-1.8"/>
<vertex x="2.05" y="-1.65"/>
<vertex x="2.55" y="-1.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="-1.825"/>
<vertex x="2.125" y="-1.825"/>
<vertex x="2.075" y="-1.775"/>
<vertex x="2.075" y="-1.675"/>
<vertex x="2.525" y="-1.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="-1.35"/>
<vertex x="2.05" y="-1.35"/>
<vertex x="2.05" y="-1.15"/>
<vertex x="2.55" y="-1.15"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="-1.325"/>
<vertex x="2.075" y="-1.325"/>
<vertex x="2.075" y="-1.175"/>
<vertex x="2.525" y="-1.175"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="-0.85"/>
<vertex x="2.05" y="-0.85"/>
<vertex x="2.05" y="-0.65"/>
<vertex x="2.55" y="-0.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="-0.825"/>
<vertex x="2.075" y="-0.825"/>
<vertex x="2.075" y="-0.675"/>
<vertex x="2.525" y="-0.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="-0.35"/>
<vertex x="2.05" y="-0.35"/>
<vertex x="2.05" y="-0.15"/>
<vertex x="2.55" y="-0.15"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="-0.325"/>
<vertex x="2.075" y="-0.325"/>
<vertex x="2.075" y="-0.175"/>
<vertex x="2.525" y="-0.175"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="0.15"/>
<vertex x="2.05" y="0.15"/>
<vertex x="2.05" y="0.35"/>
<vertex x="2.55" y="0.35"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="0.175"/>
<vertex x="2.075" y="0.175"/>
<vertex x="2.075" y="0.325"/>
<vertex x="2.525" y="0.325"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="0.65"/>
<vertex x="2.05" y="0.65"/>
<vertex x="2.05" y="0.85"/>
<vertex x="2.55" y="0.85"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="0.675"/>
<vertex x="2.075" y="0.675"/>
<vertex x="2.075" y="0.825"/>
<vertex x="2.525" y="0.825"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="1.15"/>
<vertex x="2.05" y="1.15"/>
<vertex x="2.05" y="1.35"/>
<vertex x="2.55" y="1.35"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="1.175"/>
<vertex x="2.075" y="1.175"/>
<vertex x="2.075" y="1.325"/>
<vertex x="2.525" y="1.325"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="2.55" y="1.85"/>
<vertex x="2.1" y="1.85"/>
<vertex x="2.05" y="1.8"/>
<vertex x="2.05" y="1.65"/>
<vertex x="2.55" y="1.65"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="2.525" y="1.825"/>
<vertex x="2.125" y="1.825"/>
<vertex x="2.075" y="1.775"/>
<vertex x="2.075" y="1.675"/>
<vertex x="2.525" y="1.675"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="1.85" y="2.55"/>
<vertex x="1.85" y="2.1"/>
<vertex x="1.8" y="2.05"/>
<vertex x="1.65" y="2.05"/>
<vertex x="1.65" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="1.825" y="2.525"/>
<vertex x="1.825" y="2.125"/>
<vertex x="1.775" y="2.075"/>
<vertex x="1.675" y="2.075"/>
<vertex x="1.675" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="1.35" y="2.55"/>
<vertex x="1.35" y="2.05"/>
<vertex x="1.15" y="2.05"/>
<vertex x="1.15" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="1.325" y="2.525"/>
<vertex x="1.325" y="2.075"/>
<vertex x="1.175" y="2.075"/>
<vertex x="1.175" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="0.85" y="2.55"/>
<vertex x="0.85" y="2.05"/>
<vertex x="0.65" y="2.05"/>
<vertex x="0.65" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="0.825" y="2.525"/>
<vertex x="0.825" y="2.075"/>
<vertex x="0.675" y="2.075"/>
<vertex x="0.675" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="0.35" y="2.55"/>
<vertex x="0.35" y="2.05"/>
<vertex x="0.15" y="2.05"/>
<vertex x="0.15" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="0.325" y="2.525"/>
<vertex x="0.325" y="2.075"/>
<vertex x="0.175" y="2.075"/>
<vertex x="0.175" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-0.15" y="2.55"/>
<vertex x="-0.15" y="2.05"/>
<vertex x="-0.35" y="2.05"/>
<vertex x="-0.35" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-0.175" y="2.525"/>
<vertex x="-0.175" y="2.075"/>
<vertex x="-0.325" y="2.075"/>
<vertex x="-0.325" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-0.65" y="2.55"/>
<vertex x="-0.65" y="2.05"/>
<vertex x="-0.85" y="2.05"/>
<vertex x="-0.85" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-0.675" y="2.525"/>
<vertex x="-0.675" y="2.075"/>
<vertex x="-0.825" y="2.075"/>
<vertex x="-0.825" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-1.15" y="2.55"/>
<vertex x="-1.15" y="2.05"/>
<vertex x="-1.35" y="2.05"/>
<vertex x="-1.35" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-1.175" y="2.525"/>
<vertex x="-1.175" y="2.075"/>
<vertex x="-1.325" y="2.075"/>
<vertex x="-1.325" y="2.525"/>
</polygon>
<polygon width="0.1016" layer="29">
<vertex x="-1.85" y="2.55"/>
<vertex x="-1.85" y="2.1"/>
<vertex x="-1.8" y="2.05"/>
<vertex x="-1.65" y="2.05"/>
<vertex x="-1.65" y="2.55"/>
</polygon>
<polygon width="0.1016" layer="31">
<vertex x="-1.825" y="2.525"/>
<vertex x="-1.825" y="2.125"/>
<vertex x="-1.775" y="2.075"/>
<vertex x="-1.675" y="2.075"/>
<vertex x="-1.675" y="2.525"/>
</polygon>
<smd name="9" x="-2.3" y="-2.25" dx="0.6" dy="0.3" layer="1" roundness="30" stop="no" cream="no"/>
<smd name="18" x="2.25" y="-2.8" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R90" stop="no" cream="no"/>
<smd name="19" x="2.8" y="-2.25" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R180" stop="no" cream="no"/>
<smd name="28" x="2.25" y="2.3" dx="0.6" dy="0.3" layer="1" roundness="30" rot="R270" stop="no" cream="no"/>
</package>
</packages>
<symbols>
<symbol name="BMP085">
<pin name="SCB" x="-17.78" y="2.54" length="middle" direction="nc"/>
<pin name="VDD" x="-17.78" y="0" length="middle" direction="pwr"/>
<pin name="VDDIO" x="-17.78" y="-2.54" length="middle" direction="pwr"/>
<pin name="SDO" x="17.78" y="-2.54" length="middle" direction="nc" rot="R180"/>
<pin name="SCL" x="17.78" y="0" length="middle" direction="in" rot="R180"/>
<pin name="SDA" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="GND" x="0" y="17.78" length="middle" direction="pwr" rot="R270"/>
<wire x1="-12.7" y1="-12.7" x2="12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="12.7" y1="-12.7" x2="12.7" y2="12.7" width="0.254" layer="94"/>
<wire x1="12.7" y1="12.7" x2="-12.7" y2="12.7" width="0.254" layer="94"/>
<wire x1="-12.7" y1="12.7" x2="-12.7" y2="-12.7" width="0.254" layer="94"/>
<text x="-5.08" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="0" size="1.778" layer="95">BMP085</text>
<text x="-2.54" y="-2.54" size="1.778" layer="95">LGA7</text>
<circle x="-10.668" y="10.668" radius="0.567959375" width="0.254" layer="94"/>
</symbol>
<symbol name="DBG_SWD_CON">
<pin name="+3.3V" x="-12.7" y="10.16" length="middle" direction="pwr"/>
<pin name="GND" x="-12.7" y="7.62" length="middle" direction="pwr"/>
<pin name="SWCLK" x="-12.7" y="5.08" length="middle" direction="out"/>
<pin name="SWDIO" x="-12.7" y="2.54" length="middle"/>
<wire x1="-7.62" y1="12.7" x2="2.54" y2="12.7" width="0.254" layer="94"/>
<wire x1="2.54" y1="12.7" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="-7.62" y2="0" width="0.254" layer="94"/>
<wire x1="-7.62" y1="0" x2="-7.62" y2="12.7" width="0.254" layer="94"/>
<text x="-7.62" y="15.24" size="1.27" layer="95">&gt;NAME</text>
<text x="-7.62" y="-2.54" size="1.27" layer="95">PLS04</text>
</symbol>
<symbol name="DBG_UART_CON">
<pin name="+3.3V" x="-5.08" y="7.62" length="middle" direction="pwr"/>
<pin name="GND" x="-5.08" y="5.08" length="middle" direction="pwr"/>
<pin name="RXD" x="-5.08" y="0" length="middle" direction="in"/>
<pin name="TXD" x="-5.08" y="2.54" length="middle" direction="out"/>
<wire x1="0" y1="10.16" x2="10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="10.16" x2="10.16" y2="-2.54" width="0.254" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="10.16" width="0.254" layer="94"/>
<text x="0" y="12.7" size="1.778" layer="95">&gt;NAME</text>
<text x="0" y="-5.08" size="1.778" layer="95">PLS04</text>
</symbol>
<symbol name="HMC5883">
<pin name="SCL" x="-17.78" y="5.08" length="middle" direction="in"/>
<pin name="VDD" x="-17.78" y="2.54" length="middle" direction="pwr"/>
<pin name="NC1" x="-17.78" y="0" length="middle" direction="nc"/>
<pin name="S1" x="-17.78" y="-2.54" length="middle"/>
<pin name="NC2" x="-2.54" y="-17.78" length="middle" direction="nc" rot="R90"/>
<pin name="NC3" x="0" y="-17.78" length="middle" direction="nc" rot="R90"/>
<pin name="NC4" x="2.54" y="-17.78" length="middle" direction="nc" rot="R90"/>
<pin name="SETP" x="5.08" y="-17.78" length="middle" rot="R90"/>
<pin name="GND1" x="20.32" y="-2.54" length="middle" direction="pwr" rot="R180"/>
<pin name="C1" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="GND2" x="20.32" y="2.54" length="middle" direction="pwr" rot="R180"/>
<pin name="SETC" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="VDDIO" x="5.08" y="20.32" length="middle" direction="pwr" rot="R270"/>
<pin name="NC5" x="2.54" y="20.32" length="middle" direction="nc" rot="R270"/>
<pin name="DRDY" x="0" y="20.32" length="middle" direction="out" rot="R270"/>
<pin name="SDA" x="-2.54" y="20.32" length="middle" rot="R270"/>
<wire x1="-12.7" y1="15.24" x2="15.24" y2="15.24" width="0.254" layer="94"/>
<wire x1="15.24" y1="15.24" x2="15.24" y2="-12.7" width="0.254" layer="94"/>
<wire x1="15.24" y1="-12.7" x2="-12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-12.7" x2="-12.7" y2="15.24" width="0.254" layer="94"/>
<text x="-5.08" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="0" size="1.778" layer="95">HMC5883L</text>
<text x="-5.08" y="-2.54" size="1.778" layer="95">LPCC16</text>
<circle x="-10.922" y="13.462" radius="0.567959375" width="0.254" layer="94"/>
</symbol>
<symbol name="MAIN_CON">
<pin name="DRDY" x="-7.62" y="7.62" length="middle" direction="in"/>
<pin name="TXD" x="-7.62" y="5.08" length="middle" direction="out"/>
<pin name="RXD" x="-7.62" y="2.54" length="middle" direction="in"/>
<pin name="GND" x="-7.62" y="0" length="middle" direction="pwr"/>
<pin name="+5V" x="-7.62" y="-2.54" length="middle" direction="pwr"/>
<wire x1="-2.54" y1="10.16" x2="7.62" y2="10.16" width="0.254" layer="94"/>
<wire x1="7.62" y1="10.16" x2="7.62" y2="-5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="-5.08" x2="-2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="10.16" width="0.254" layer="94"/>
<text x="-2.54" y="12.7" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-7.62" size="1.778" layer="95">PLS05</text>
</symbol>
<symbol name="MPU6050">
<pin name="CLKIN" x="-22.86" y="7.62" length="middle" direction="in"/>
<pin name="NC1" x="-22.86" y="5.08" length="middle" direction="nc"/>
<pin name="NC2" x="-22.86" y="2.54" length="middle" direction="nc"/>
<pin name="NC3" x="-22.86" y="0" length="middle" direction="nc"/>
<pin name="NC4" x="-22.86" y="-2.54" length="middle" direction="nc"/>
<pin name="AUX_DA" x="-22.86" y="-5.08" length="middle"/>
<pin name="AUX_CL" x="-5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="VLOGIC" x="-2.54" y="-22.86" length="middle" direction="pwr" rot="R90"/>
<pin name="AD0" x="0" y="-22.86" length="middle" direction="in" rot="R90"/>
<pin name="REGOUT" x="2.54" y="-22.86" length="middle" rot="R90"/>
<pin name="FSYNC" x="5.08" y="-22.86" length="middle" rot="R90"/>
<pin name="INT" x="7.62" y="-22.86" length="middle" direction="out" rot="R90"/>
<pin name="VDD" x="25.4" y="-5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="NC5" x="25.4" y="-2.54" length="middle" direction="nc" rot="R180"/>
<pin name="NC6" x="25.4" y="0" length="middle" direction="nc" rot="R180"/>
<pin name="NC7" x="25.4" y="2.54" length="middle" direction="nc" rot="R180"/>
<pin name="NC8" x="25.4" y="5.08" length="middle" direction="nc" rot="R180"/>
<pin name="GND" x="25.4" y="7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="RESV1" x="7.62" y="25.4" length="middle" direction="nc" rot="R270"/>
<pin name="CPOUT" x="5.08" y="25.4" length="middle" rot="R270"/>
<pin name="RESV2" x="2.54" y="25.4" length="middle" direction="nc" rot="R270"/>
<pin name="CLKOUT" x="0" y="25.4" length="middle" rot="R270"/>
<pin name="SCL" x="-2.54" y="25.4" length="middle" direction="in" rot="R270"/>
<pin name="SDA" x="-5.08" y="25.4" length="middle" rot="R270"/>
<wire x1="-17.78" y1="20.32" x2="20.32" y2="20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="20.32" x2="20.32" y2="-17.78" width="0.254" layer="94"/>
<wire x1="20.32" y1="-17.78" x2="-17.78" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-17.78" x2="-17.78" y2="20.32" width="0.254" layer="94"/>
<text x="-2.54" y="5.08" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="2.54" size="1.778" layer="95">MPU6050</text>
<text x="-2.54" y="0" size="1.778" layer="95">QFN24</text>
<circle x="-16.002" y="18.542" radius="0.71841875" width="0.254" layer="94"/>
</symbol>
<symbol name="STM32F103T">
<pin name="VDD_3" x="-25.4" y="10.16" length="middle"/>
<pin name="OSC_IN/PD0" x="-25.4" y="7.62" length="middle"/>
<pin name="OSC_OUT/PD1" x="-25.4" y="5.08" length="middle"/>
<pin name="NRST" x="-25.4" y="2.54" length="middle"/>
<pin name="VSSA" x="-25.4" y="0" length="middle"/>
<pin name="VDDA" x="-25.4" y="-2.54" length="middle"/>
<pin name="PA0-WKUP" x="-25.4" y="-5.08" length="middle"/>
<pin name="PA1" x="-25.4" y="-7.62" length="middle"/>
<pin name="PA2" x="-25.4" y="-10.16" length="middle"/>
<pin name="PA3" x="-10.16" y="-25.4" length="middle" rot="R90"/>
<pin name="PA4" x="-7.62" y="-25.4" length="middle" rot="R90"/>
<pin name="PA5" x="-5.08" y="-25.4" length="middle" rot="R90"/>
<pin name="PA6" x="-2.54" y="-25.4" length="middle" rot="R90"/>
<pin name="PA7" x="0" y="-25.4" length="middle" rot="R90"/>
<pin name="PB0" x="2.54" y="-25.4" length="middle" rot="R90"/>
<pin name="PB1" x="5.08" y="-25.4" length="middle" rot="R90"/>
<pin name="PB2" x="7.62" y="-25.4" length="middle" rot="R90"/>
<pin name="VSS_1" x="10.16" y="-25.4" length="middle" rot="R90"/>
<pin name="VDD_1" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="PA8" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="PA9" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="PA10" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="PA11" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="PA12" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="PA13" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="VSS_2" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="VDD_2" x="25.4" y="10.16" length="middle" rot="R180"/>
<pin name="PA14" x="10.16" y="25.4" length="middle" rot="R270"/>
<pin name="PA15" x="7.62" y="25.4" length="middle" rot="R270"/>
<pin name="PB3" x="5.08" y="25.4" length="middle" rot="R270"/>
<pin name="PB4" x="2.54" y="25.4" length="middle" rot="R270"/>
<pin name="PB5" x="0" y="25.4" length="middle" rot="R270"/>
<pin name="PB6" x="-2.54" y="25.4" length="middle" rot="R270"/>
<pin name="PB7" x="-5.08" y="25.4" length="middle" rot="R270"/>
<pin name="BOOT0" x="-7.62" y="25.4" length="middle" rot="R270"/>
<pin name="VSS_3" x="-10.16" y="25.4" length="middle" rot="R270"/>
<wire x1="-20.32" y1="-20.32" x2="-20.32" y2="20.32" width="0.254" layer="94"/>
<wire x1="-20.32" y1="20.32" x2="20.32" y2="20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="20.32" x2="20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="-20.32" x2="-20.32" y2="-20.32" width="0.254" layer="94"/>
<text x="-2.54" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.778" layer="95">QFN36</text>
<circle x="-18.796" y="18.796" radius="0.567959375" width="0.254" layer="94"/>
<text x="-7.62" y="-2.54" size="1.778" layer="95">STM32F103T</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="BMP085">
<gates>
<gate name="G$1" symbol="BMP085" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LGA7">
<connects>
<connect gate="G$1" pin="GND" pad="7"/>
<connect gate="G$1" pin="SCB" pad="1"/>
<connect gate="G$1" pin="SCL" pad="5"/>
<connect gate="G$1" pin="SDA" pad="6"/>
<connect gate="G$1" pin="SDO" pad="4"/>
<connect gate="G$1" pin="VDD" pad="2"/>
<connect gate="G$1" pin="VDDIO" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DBG_SWD_CON">
<gates>
<gate name="G$1" symbol="DBG_SWD_CON" x="5.08" y="-5.08"/>
</gates>
<devices>
<device name="" package="PLS04">
<connects>
<connect gate="G$1" pin="+3.3V" pad="1"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="SWCLK" pad="3"/>
<connect gate="G$1" pin="SWDIO" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DBG_UART_CON">
<gates>
<gate name="G$1" symbol="DBG_UART_CON" x="-2.54" y="-2.54"/>
</gates>
<devices>
<device name="" package="PLS04">
<connects>
<connect gate="G$1" pin="+3.3V" pad="1"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="RXD" pad="4"/>
<connect gate="G$1" pin="TXD" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HMC5883">
<description>Package just for schematics. Do not use for board.</description>
<gates>
<gate name="G$1" symbol="HMC5883" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN16-4X4">
<connects>
<connect gate="G$1" pin="C1" pad="10"/>
<connect gate="G$1" pin="DRDY" pad="15"/>
<connect gate="G$1" pin="GND1" pad="9"/>
<connect gate="G$1" pin="GND2" pad="11"/>
<connect gate="G$1" pin="NC1" pad="3"/>
<connect gate="G$1" pin="NC2" pad="5"/>
<connect gate="G$1" pin="NC3" pad="6"/>
<connect gate="G$1" pin="NC4" pad="7"/>
<connect gate="G$1" pin="NC5" pad="14"/>
<connect gate="G$1" pin="S1" pad="4"/>
<connect gate="G$1" pin="SCL" pad="1"/>
<connect gate="G$1" pin="SDA" pad="16"/>
<connect gate="G$1" pin="SETC" pad="12"/>
<connect gate="G$1" pin="SETP" pad="8"/>
<connect gate="G$1" pin="VDD" pad="2"/>
<connect gate="G$1" pin="VDDIO" pad="13"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MAIN_CON">
<gates>
<gate name="G$1" symbol="MAIN_CON" x="0" y="-2.54"/>
</gates>
<devices>
<device name="" package="PLS05">
<connects>
<connect gate="G$1" pin="+5V" pad="5"/>
<connect gate="G$1" pin="DRDY" pad="1"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="RXD" pad="3"/>
<connect gate="G$1" pin="TXD" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MPU6050">
<description>Package for schematics only.</description>
<gates>
<gate name="G$1" symbol="MPU6050" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN24-4X4">
<connects>
<connect gate="G$1" pin="AD0" pad="9"/>
<connect gate="G$1" pin="AUX_CL" pad="7"/>
<connect gate="G$1" pin="AUX_DA" pad="6"/>
<connect gate="G$1" pin="CLKIN" pad="1"/>
<connect gate="G$1" pin="CLKOUT" pad="22"/>
<connect gate="G$1" pin="CPOUT" pad="20"/>
<connect gate="G$1" pin="FSYNC" pad="11"/>
<connect gate="G$1" pin="GND" pad="18"/>
<connect gate="G$1" pin="INT" pad="12"/>
<connect gate="G$1" pin="NC1" pad="2"/>
<connect gate="G$1" pin="NC2" pad="3"/>
<connect gate="G$1" pin="NC3" pad="4"/>
<connect gate="G$1" pin="NC4" pad="5"/>
<connect gate="G$1" pin="NC5" pad="14"/>
<connect gate="G$1" pin="NC6" pad="15"/>
<connect gate="G$1" pin="NC7" pad="16"/>
<connect gate="G$1" pin="NC8" pad="17"/>
<connect gate="G$1" pin="REGOUT" pad="10"/>
<connect gate="G$1" pin="RESV1" pad="19"/>
<connect gate="G$1" pin="RESV2" pad="21"/>
<connect gate="G$1" pin="SCL" pad="23"/>
<connect gate="G$1" pin="SDA" pad="24"/>
<connect gate="G$1" pin="VDD" pad="13"/>
<connect gate="G$1" pin="VLOGIC" pad="8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STM32F103T">
<description>Package not werifyed.</description>
<gates>
<gate name="G$1" symbol="STM32F103T" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN36">
<connects>
<connect gate="G$1" pin="BOOT0" pad="35"/>
<connect gate="G$1" pin="NRST" pad="4"/>
<connect gate="G$1" pin="OSC_IN/PD0" pad="2"/>
<connect gate="G$1" pin="OSC_OUT/PD1" pad="3"/>
<connect gate="G$1" pin="PA0-WKUP" pad="7"/>
<connect gate="G$1" pin="PA1" pad="8"/>
<connect gate="G$1" pin="PA10" pad="22"/>
<connect gate="G$1" pin="PA11" pad="23"/>
<connect gate="G$1" pin="PA12" pad="24"/>
<connect gate="G$1" pin="PA13" pad="25"/>
<connect gate="G$1" pin="PA14" pad="28"/>
<connect gate="G$1" pin="PA15" pad="29"/>
<connect gate="G$1" pin="PA2" pad="9"/>
<connect gate="G$1" pin="PA3" pad="10"/>
<connect gate="G$1" pin="PA4" pad="11"/>
<connect gate="G$1" pin="PA5" pad="12"/>
<connect gate="G$1" pin="PA6" pad="13"/>
<connect gate="G$1" pin="PA7" pad="14"/>
<connect gate="G$1" pin="PA8" pad="20"/>
<connect gate="G$1" pin="PA9" pad="21"/>
<connect gate="G$1" pin="PB0" pad="15"/>
<connect gate="G$1" pin="PB1" pad="16"/>
<connect gate="G$1" pin="PB2" pad="17"/>
<connect gate="G$1" pin="PB3" pad="30"/>
<connect gate="G$1" pin="PB4" pad="31"/>
<connect gate="G$1" pin="PB5" pad="32"/>
<connect gate="G$1" pin="PB6" pad="33"/>
<connect gate="G$1" pin="PB7" pad="34"/>
<connect gate="G$1" pin="VDDA" pad="6"/>
<connect gate="G$1" pin="VDD_1" pad="19"/>
<connect gate="G$1" pin="VDD_2" pad="27"/>
<connect gate="G$1" pin="VDD_3" pad="1"/>
<connect gate="G$1" pin="VSSA" pad="5"/>
<connect gate="G$1" pin="VSS_1" pad="18"/>
<connect gate="G$1" pin="VSS_2" pad="26"/>
<connect gate="G$1" pin="VSS_3" pad="36"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="DD4" library="elem" deviceset="BMP085" device=""/>
<part name="X3" library="elem" deviceset="DBG_SWD_CON" device=""/>
<part name="X2" library="elem" deviceset="DBG_UART_CON" device=""/>
<part name="DD3" library="elem" deviceset="HMC5883" device=""/>
<part name="X1" library="elem" deviceset="MAIN_CON" device=""/>
<part name="DD2" library="elem" deviceset="MPU6050" device=""/>
<part name="DD1" library="elem" deviceset="STM32F103T" device=""/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
<part name="GND7" library="supply1" deviceset="GND" device=""/>
<part name="P+1" library="supply1" deviceset="+5V" device=""/>
<part name="+3V1" library="supply1" deviceset="+3V3" device=""/>
<part name="+3V2" library="supply1" deviceset="+3V3" device=""/>
<part name="GND8" library="supply1" deviceset="GND" device=""/>
<part name="GND9" library="supply1" deviceset="GND" device=""/>
<part name="GND10" library="supply1" deviceset="GND" device=""/>
<part name="GND11" library="supply1" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="124.46" y="-66.04" size="1.778" layer="97">New BMP085 in LGA7, no EOC pin.</text>
</plain>
<instances>
<instance part="DD4" gate="G$1" x="137.16" y="-48.26"/>
<instance part="X3" gate="G$1" x="-25.4" y="-27.94" rot="MR0"/>
<instance part="X2" gate="G$1" x="-17.78" y="-5.08" rot="MR0"/>
<instance part="DD3" gate="G$1" x="205.74" y="27.94"/>
<instance part="X1" gate="G$1" x="-20.32" y="17.78" rot="MR0"/>
<instance part="DD2" gate="G$1" x="137.16" y="27.94"/>
<instance part="DD1" gate="G$1" x="50.8" y="-5.08"/>
<instance part="GND1" gate="1" x="-10.16" y="10.16"/>
<instance part="GND2" gate="1" x="-10.16" y="-10.16"/>
<instance part="GND3" gate="1" x="-10.16" y="-30.48"/>
<instance part="GND4" gate="1" x="60.96" y="-43.18"/>
<instance part="GND5" gate="1" x="88.9" y="2.54" rot="R90"/>
<instance part="GND6" gate="1" x="40.64" y="33.02" rot="R180"/>
<instance part="GND7" gate="1" x="10.16" y="-5.08" rot="R270"/>
<instance part="P+1" gate="1" x="-2.54" y="15.24" rot="R270"/>
<instance part="+3V1" gate="G$1" x="-5.08" y="2.54" rot="R270"/>
<instance part="+3V2" gate="G$1" x="-5.08" y="-17.78" rot="R270"/>
<instance part="GND8" gate="1" x="137.16" y="-22.86" rot="R180"/>
<instance part="GND9" gate="1" x="233.68" y="12.7"/>
<instance part="GND10" gate="1" x="167.64" y="10.16"/>
<instance part="GND11" gate="1" x="96.52" y="35.56" rot="R270"/>
</instances>
<busses>
</busses>
<nets>
<net name="TXD2" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="TXD"/>
<wire x1="-12.7" y1="22.86" x2="0" y2="22.86" width="0.1524" layer="91"/>
<label x="-7.62" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA2"/>
<wire x1="25.4" y1="-15.24" x2="12.7" y2="-15.24" width="0.1524" layer="91"/>
<label x="12.7" y="-15.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="RXD2" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="RXD"/>
<wire x1="-12.7" y1="20.32" x2="0" y2="20.32" width="0.1524" layer="91"/>
<label x="-7.62" y="20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA3"/>
<wire x1="40.64" y1="-30.48" x2="40.64" y2="-48.26" width="0.1524" layer="91"/>
<label x="40.64" y="-48.26" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="DRDY" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="DRDY"/>
<wire x1="-12.7" y1="25.4" x2="0" y2="25.4" width="0.1524" layer="91"/>
<label x="-7.62" y="25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA1"/>
<wire x1="25.4" y1="-12.7" x2="12.7" y2="-12.7" width="0.1524" layer="91"/>
<label x="12.7" y="-12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="GND"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="-12.7" y1="17.78" x2="-10.16" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="17.78" x2="-10.16" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X2" gate="G$1" pin="GND"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="-12.7" y1="0" x2="-10.16" y2="0" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="0" x2="-10.16" y2="-7.62" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X3" gate="G$1" pin="GND"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="-12.7" y1="-20.32" x2="-10.16" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="-20.32" x2="-10.16" y2="-27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND7" gate="1" pin="GND"/>
<pinref part="DD1" gate="G$1" pin="VSSA"/>
<wire x1="12.7" y1="-5.08" x2="25.4" y2="-5.08" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="VSS_1"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="60.96" y1="-30.48" x2="60.96" y2="-40.64" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="VSS_2"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="76.2" y1="2.54" x2="86.36" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="40.64" y1="30.48" x2="40.64" y2="27.94" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="BOOT0"/>
<wire x1="43.18" y1="20.32" x2="43.18" y2="27.94" width="0.1524" layer="91"/>
<wire x1="43.18" y1="27.94" x2="40.64" y2="27.94" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="VSS_3"/>
<wire x1="40.64" y1="20.32" x2="40.64" y2="27.94" width="0.1524" layer="91"/>
<junction x="40.64" y="27.94"/>
</segment>
<segment>
<pinref part="DD2" gate="G$1" pin="GND"/>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="162.56" y1="35.56" x2="167.64" y2="35.56" width="0.1524" layer="91"/>
<wire x1="167.64" y1="35.56" x2="167.64" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD3" gate="G$1" pin="GND2"/>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="226.06" y1="30.48" x2="233.68" y2="30.48" width="0.1524" layer="91"/>
<wire x1="233.68" y1="30.48" x2="233.68" y2="25.4" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="GND1"/>
<wire x1="233.68" y1="25.4" x2="233.68" y2="15.24" width="0.1524" layer="91"/>
<wire x1="226.06" y1="25.4" x2="233.68" y2="25.4" width="0.1524" layer="91"/>
<junction x="233.68" y="25.4"/>
</segment>
<segment>
<pinref part="GND8" gate="1" pin="GND"/>
<pinref part="DD4" gate="G$1" pin="GND"/>
<wire x1="137.16" y1="-25.4" x2="137.16" y2="-30.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD2" gate="G$1" pin="CLKIN"/>
<wire x1="114.3" y1="35.56" x2="99.06" y2="35.56" width="0.1524" layer="91"/>
<pinref part="GND11" gate="1" pin="GND"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="X1" gate="G$1" pin="+5V"/>
<pinref part="P+1" gate="1" pin="+5V"/>
<wire x1="-12.7" y1="15.24" x2="-5.08" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="X2" gate="G$1" pin="+3.3V"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<wire x1="-12.7" y1="2.54" x2="-7.62" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="X3" gate="G$1" pin="+3.3V"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<wire x1="-12.7" y1="-17.78" x2="-7.62" y2="-17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TXD1" class="0">
<segment>
<pinref part="X2" gate="G$1" pin="TXD"/>
<wire x1="-12.7" y1="-2.54" x2="0" y2="-2.54" width="0.1524" layer="91"/>
<label x="-7.62" y="-2.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA9"/>
<wire x1="76.2" y1="-10.16" x2="88.9" y2="-10.16" width="0.1524" layer="91"/>
<label x="78.74" y="-10.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="RXD1" class="0">
<segment>
<pinref part="X2" gate="G$1" pin="RXD"/>
<wire x1="-12.7" y1="-5.08" x2="0" y2="-5.08" width="0.1524" layer="91"/>
<label x="-7.62" y="-5.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA10"/>
<wire x1="76.2" y1="-7.62" x2="88.9" y2="-7.62" width="0.1524" layer="91"/>
<label x="78.74" y="-7.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="SWCLK" class="0">
<segment>
<pinref part="X3" gate="G$1" pin="SWCLK"/>
<wire x1="-12.7" y1="-22.86" x2="2.54" y2="-22.86" width="0.1524" layer="91"/>
<label x="-7.62" y="-22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA14"/>
<wire x1="60.96" y1="20.32" x2="60.96" y2="35.56" width="0.1524" layer="91"/>
<label x="60.96" y="22.86" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="SWDIO" class="0">
<segment>
<pinref part="X3" gate="G$1" pin="SWDIO"/>
<wire x1="-12.7" y1="-25.4" x2="2.54" y2="-25.4" width="0.1524" layer="91"/>
<label x="-7.62" y="-25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA13"/>
<wire x1="76.2" y1="0" x2="86.36" y2="0" width="0.1524" layer="91"/>
<label x="78.74" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="I2C1_SDA" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="SDA"/>
<wire x1="132.08" y1="53.34" x2="132.08" y2="68.58" width="0.1524" layer="91"/>
<label x="132.08" y="55.88" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PB7"/>
<wire x1="45.72" y1="20.32" x2="45.72" y2="35.56" width="0.1524" layer="91"/>
<label x="45.72" y="22.86" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<wire x1="154.94" y1="-45.72" x2="170.18" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="DD4" gate="G$1" pin="SDA"/>
<label x="157.48" y="-45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="I2C1_SCL" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="SCL"/>
<wire x1="134.62" y1="53.34" x2="134.62" y2="68.58" width="0.1524" layer="91"/>
<label x="134.62" y="55.88" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PB6"/>
<wire x1="48.26" y1="20.32" x2="48.26" y2="35.56" width="0.1524" layer="91"/>
<label x="48.26" y="22.86" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD4" gate="G$1" pin="SCL"/>
<wire x1="154.94" y1="-48.26" x2="170.18" y2="-48.26" width="0.1524" layer="91"/>
<label x="157.48" y="-48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="BMP_EOC" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PA4"/>
<wire x1="43.18" y1="-30.48" x2="43.18" y2="-48.26" width="0.1524" layer="91"/>
<label x="43.18" y="-48.26" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="RUN_LED" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PA8"/>
<wire x1="76.2" y1="-12.7" x2="88.9" y2="-12.7" width="0.1524" layer="91"/>
<label x="78.74" y="-12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="MPU_INT" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="INT"/>
<wire x1="144.78" y1="5.08" x2="144.78" y2="-12.7" width="0.1524" layer="91"/>
<label x="144.78" y="-12.7" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA6"/>
<wire x1="48.26" y1="-30.48" x2="48.26" y2="-48.26" width="0.1524" layer="91"/>
<label x="48.26" y="-48.26" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="MPU_FSYNC" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="FSYNC"/>
<wire x1="142.24" y1="5.08" x2="142.24" y2="-12.7" width="0.1524" layer="91"/>
<label x="142.24" y="-12.7" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA7"/>
<wire x1="50.8" y1="-30.48" x2="50.8" y2="-48.26" width="0.1524" layer="91"/>
<label x="50.8" y="-48.26" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="AUX_DA" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="AUX_DA"/>
<wire x1="114.3" y1="22.86" x2="99.06" y2="22.86" width="0.1524" layer="91"/>
<label x="99.06" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD3" gate="G$1" pin="SDA"/>
<wire x1="203.2" y1="48.26" x2="203.2" y2="66.04" width="0.1524" layer="91"/>
<label x="203.2" y="50.8" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="AUX_CL" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="AUX_CL"/>
<wire x1="132.08" y1="5.08" x2="132.08" y2="-12.7" width="0.1524" layer="91"/>
<label x="132.08" y="-12.7" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD3" gate="G$1" pin="SCL"/>
<wire x1="187.96" y1="33.02" x2="177.8" y2="33.02" width="0.1524" layer="91"/>
<label x="177.8" y="33.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="HMC_DRDY" class="0">
<segment>
<pinref part="DD3" gate="G$1" pin="DRDY"/>
<wire x1="205.74" y1="48.26" x2="205.74" y2="66.04" width="0.1524" layer="91"/>
<label x="205.74" y="50.8" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA5"/>
<wire x1="45.72" y1="-30.48" x2="45.72" y2="-48.26" width="0.1524" layer="91"/>
<label x="45.72" y="-48.26" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
