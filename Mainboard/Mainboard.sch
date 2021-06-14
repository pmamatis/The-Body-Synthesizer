<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
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
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
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
<library name="NUCLEO-F746ZG">
<packages>
<package name="MODULE_NUCLEO-F746ZG">
<wire x1="-35" y1="41.17" x2="-35" y2="-64.67" width="0.127" layer="51"/>
<wire x1="-35" y1="-64.67" x2="-33" y2="-66.67" width="0.127" layer="51" curve="90"/>
<wire x1="-33" y1="-66.67" x2="33" y2="-66.67" width="0.127" layer="51"/>
<wire x1="33" y1="-66.67" x2="35" y2="-64.67" width="0.127" layer="51" curve="90"/>
<wire x1="35" y1="-64.67" x2="35" y2="41.17" width="0.127" layer="51"/>
<wire x1="35" y1="42.11" x2="35" y2="64.67" width="0.127" layer="51"/>
<wire x1="35" y1="64.67" x2="33" y2="66.67" width="0.127" layer="51" curve="90"/>
<wire x1="33" y1="66.67" x2="-33" y2="66.67" width="0.127" layer="51"/>
<wire x1="-33" y1="66.67" x2="-35" y2="64.67" width="0.127" layer="51" curve="90"/>
<wire x1="-35" y1="64.67" x2="-35" y2="42.11" width="0.127" layer="51"/>
<wire x1="-35" y1="41.17" x2="-35" y2="-64.67" width="0.127" layer="21"/>
<wire x1="-35" y1="-64.67" x2="-33" y2="-66.67" width="0.127" layer="21" curve="90"/>
<wire x1="-33" y1="-66.67" x2="33" y2="-66.67" width="0.127" layer="21"/>
<wire x1="33" y1="-66.67" x2="35" y2="-64.67" width="0.127" layer="21" curve="90"/>
<wire x1="35" y1="-64.67" x2="35" y2="41.17" width="0.127" layer="21"/>
<wire x1="35" y1="42.11" x2="35" y2="64.67" width="0.127" layer="21"/>
<wire x1="35" y1="64.67" x2="33" y2="66.67" width="0.127" layer="21" curve="90"/>
<wire x1="33" y1="66.67" x2="-33" y2="66.67" width="0.127" layer="21"/>
<wire x1="-33" y1="66.67" x2="-35" y2="64.67" width="0.127" layer="21" curve="90"/>
<wire x1="-35" y1="64.67" x2="-35" y2="42.11" width="0.127" layer="21"/>
<circle x="-33.5" y="34.93" radius="0.1" width="0.2" layer="21"/>
<circle x="-33.5" y="34.93" radius="0.1" width="0.2" layer="51"/>
<circle x="27.46" y="34.9046" radius="0.1" width="0.2" layer="51"/>
<circle x="27.46" y="34.9046" radius="0.1" width="0.2" layer="21"/>
<circle x="-25.88" y="24.77" radius="0.1" width="0.2" layer="21"/>
<circle x="-25.88" y="24.77" radius="0.1" width="0.2" layer="51"/>
<circle x="-25.88" y="1.91" radius="0.1" width="0.2" layer="51"/>
<circle x="-25.88" y="1.91" radius="0.1" width="0.2" layer="21"/>
<circle x="19.84" y="33.914" radius="0.1" width="0.2" layer="21"/>
<circle x="19.84" y="33.914" radius="0.1" width="0.2" layer="51"/>
<circle x="19.84" y="6.99" radius="0.1" width="0.2" layer="51"/>
<circle x="19.84" y="6.99" radius="0.1" width="0.2" layer="21"/>
<wire x1="-35" y1="41.17" x2="-19.5072" y2="41.17" width="0.127" layer="21"/>
<wire x1="-16.002" y1="41.17" x2="2.9972" y2="41.17" width="0.127" layer="21"/>
<wire x1="7.62" y1="41.17" x2="14.9352" y2="41.17" width="0.127" layer="21"/>
<wire x1="18.9992" y1="41.17" x2="35" y2="41.17" width="0.127" layer="21"/>
<wire x1="-35" y1="42.11" x2="-19.5072" y2="42.11" width="0.127" layer="21"/>
<wire x1="-16.002" y1="42.11" x2="2.9972" y2="42.11" width="0.127" layer="21"/>
<wire x1="7.62" y1="42.11" x2="14.9352" y2="42.11" width="0.127" layer="21"/>
<wire x1="18.9992" y1="42.11" x2="35" y2="42.11" width="0.127" layer="21"/>
<wire x1="18.9992" y1="41.17" x2="18.9992" y2="42.11" width="0.127" layer="21" curve="-178.181"/>
<wire x1="14.9352" y1="42.11" x2="14.9352" y2="41.17" width="0.127" layer="21" curve="-178.181"/>
<wire x1="7.62" y1="41.17" x2="7.62" y2="42.11" width="0.127" layer="21" curve="-178.181"/>
<wire x1="2.9972" y1="42.11" x2="2.9972" y2="41.17" width="0.127" layer="21" curve="-178.181"/>
<wire x1="-16.002" y1="41.17" x2="-16.002" y2="42.11" width="0.127" layer="21" curve="-178.181"/>
<wire x1="-19.5072" y1="42.11" x2="-19.5072" y2="41.17" width="0.127" layer="21" curve="-178.181"/>
<wire x1="-35" y1="41.17" x2="-19.5072" y2="41.17" width="0.127" layer="51"/>
<wire x1="-16.002" y1="41.17" x2="2.9972" y2="41.17" width="0.127" layer="51"/>
<wire x1="7.62" y1="41.17" x2="14.9352" y2="41.17" width="0.127" layer="51"/>
<wire x1="18.9992" y1="41.17" x2="35" y2="41.17" width="0.127" layer="51"/>
<wire x1="-35" y1="42.11" x2="-19.5072" y2="42.11" width="0.127" layer="51"/>
<wire x1="-16.002" y1="42.11" x2="2.9972" y2="42.11" width="0.127" layer="51"/>
<wire x1="7.62" y1="42.11" x2="14.9352" y2="42.11" width="0.127" layer="51"/>
<wire x1="18.9992" y1="42.11" x2="35" y2="42.11" width="0.127" layer="51"/>
<wire x1="18.9992" y1="41.17" x2="18.9992" y2="42.11" width="0.127" layer="51" curve="-178.181"/>
<wire x1="14.9352" y1="42.11" x2="14.9352" y2="41.17" width="0.127" layer="51" curve="-178.181"/>
<wire x1="7.62" y1="41.17" x2="7.62" y2="42.11" width="0.127" layer="51" curve="-178.181"/>
<wire x1="2.9972" y1="42.11" x2="2.9972" y2="41.17" width="0.127" layer="51" curve="-178.181"/>
<wire x1="-16.002" y1="41.17" x2="-16.002" y2="42.11" width="0.127" layer="51" curve="-178.181"/>
<wire x1="-19.5072" y1="42.11" x2="-19.5072" y2="41.17" width="0.127" layer="51" curve="-178.181"/>
<text x="-34.75" y="67.33" size="1.778" layer="25">&gt;NAME</text>
<text x="-34.75" y="-67.17" size="1.778" layer="27" align="top-left">&gt;VALUE</text>
<wire x1="35.25" y1="-64.67" x2="35.25" y2="64.67" width="0.05" layer="39"/>
<wire x1="35.25" y1="64.67" x2="33" y2="66.92" width="0.05" layer="39" curve="90"/>
<wire x1="33" y1="66.92" x2="-33" y2="66.92" width="0.05" layer="39"/>
<wire x1="-33" y1="66.92" x2="-35.25" y2="64.67" width="0.05" layer="39" curve="90"/>
<wire x1="-35.25" y1="64.67" x2="-35.25" y2="-64.67" width="0.05" layer="39"/>
<wire x1="-35.25" y1="-64.67" x2="-33" y2="-66.92" width="0.05" layer="39" curve="90"/>
<wire x1="-33" y1="-66.92" x2="33" y2="-66.92" width="0.05" layer="39"/>
<wire x1="33" y1="-66.92" x2="35.25" y2="-64.67" width="0.05" layer="39" curve="90"/>
<pad name="CN11_1" x="-31.75" y="34.93" drill="1.02" shape="square"/>
<pad name="CN11_2" x="-29.21" y="34.93" drill="1.02"/>
<pad name="CN11_3" x="-31.75" y="32.39" drill="1.02"/>
<pad name="CN11_4" x="-29.21" y="32.39" drill="1.02"/>
<pad name="CN11_5" x="-31.75" y="29.85" drill="1.02"/>
<pad name="CN11_6" x="-29.21" y="29.85" drill="1.02"/>
<pad name="CN11_7" x="-31.75" y="27.31" drill="1.02"/>
<pad name="CN11_8" x="-29.21" y="27.31" drill="1.02"/>
<pad name="CN11_9" x="-31.75" y="24.77" drill="1.02"/>
<pad name="CN11_10" x="-29.21" y="24.77" drill="1.02"/>
<pad name="CN11_11" x="-31.75" y="22.23" drill="1.02"/>
<pad name="CN11_12" x="-29.21" y="22.23" drill="1.02"/>
<pad name="CN11_13" x="-31.75" y="19.69" drill="1.02"/>
<pad name="CN11_14" x="-29.21" y="19.69" drill="1.02"/>
<pad name="CN11_15" x="-31.75" y="17.15" drill="1.02"/>
<pad name="CN11_16" x="-29.21" y="17.15" drill="1.02"/>
<pad name="CN11_17" x="-31.75" y="14.61" drill="1.02"/>
<pad name="CN11_18" x="-29.21" y="14.61" drill="1.02"/>
<pad name="CN11_19" x="-31.75" y="12.07" drill="1.02"/>
<pad name="CN11_20" x="-29.21" y="12.07" drill="1.02"/>
<pad name="CN11_21" x="-31.75" y="9.53" drill="1.02"/>
<pad name="CN11_22" x="-29.21" y="9.53" drill="1.02"/>
<pad name="CN11_23" x="-31.75" y="6.99" drill="1.02"/>
<pad name="CN11_24" x="-29.21" y="6.99" drill="1.02"/>
<pad name="CN11_25" x="-31.75" y="4.45" drill="1.02"/>
<pad name="CN11_26" x="-29.21" y="4.45" drill="1.02"/>
<pad name="CN11_27" x="-31.75" y="1.91" drill="1.02"/>
<pad name="CN11_28" x="-29.21" y="1.91" drill="1.02"/>
<pad name="CN11_29" x="-31.75" y="-0.63" drill="1.02"/>
<pad name="CN11_30" x="-29.21" y="-0.63" drill="1.02"/>
<pad name="CN11_31" x="-31.75" y="-3.17" drill="1.02"/>
<pad name="CN11_32" x="-29.21" y="-3.17" drill="1.02"/>
<pad name="CN11_33" x="-31.75" y="-5.71" drill="1.02"/>
<pad name="CN11_34" x="-29.21" y="-5.71" drill="1.02"/>
<pad name="CN11_35" x="-31.75" y="-8.25" drill="1.02"/>
<pad name="CN11_36" x="-29.21" y="-8.25" drill="1.02"/>
<pad name="CN11_37" x="-31.75" y="-10.79" drill="1.02"/>
<pad name="CN11_38" x="-29.21" y="-10.79" drill="1.02"/>
<pad name="CN11_39" x="-31.75" y="-13.33" drill="1.02"/>
<pad name="CN11_40" x="-29.21" y="-13.33" drill="1.02"/>
<pad name="CN11_41" x="-31.75" y="-15.87" drill="1.02"/>
<pad name="CN11_42" x="-29.21" y="-15.87" drill="1.02"/>
<pad name="CN11_43" x="-31.75" y="-18.41" drill="1.02"/>
<pad name="CN11_44" x="-29.21" y="-18.41" drill="1.02"/>
<pad name="CN11_45" x="-31.75" y="-20.95" drill="1.02"/>
<pad name="CN11_46" x="-29.21" y="-20.95" drill="1.02"/>
<pad name="CN11_47" x="-31.75" y="-23.49" drill="1.02"/>
<pad name="CN11_48" x="-29.21" y="-23.49" drill="1.02"/>
<pad name="CN11_49" x="-31.75" y="-26.03" drill="1.02"/>
<pad name="CN11_50" x="-29.21" y="-26.03" drill="1.02"/>
<pad name="CN11_51" x="-31.75" y="-28.57" drill="1.02"/>
<pad name="CN11_52" x="-29.21" y="-28.57" drill="1.02"/>
<pad name="CN11_53" x="-31.75" y="-31.11" drill="1.02"/>
<pad name="CN11_54" x="-29.21" y="-31.11" drill="1.02"/>
<pad name="CN11_55" x="-31.75" y="-33.65" drill="1.02"/>
<pad name="CN11_56" x="-29.21" y="-33.65" drill="1.02"/>
<pad name="CN11_57" x="-31.75" y="-36.19" drill="1.02"/>
<pad name="CN11_58" x="-29.21" y="-36.19" drill="1.02"/>
<pad name="CN11_59" x="-31.75" y="-38.73" drill="1.02"/>
<pad name="CN11_60" x="-29.21" y="-38.73" drill="1.02"/>
<pad name="CN11_61" x="-31.75" y="-41.27" drill="1.02"/>
<pad name="CN11_62" x="-29.21" y="-41.27" drill="1.02"/>
<pad name="CN11_63" x="-31.75" y="-43.81" drill="1.02"/>
<pad name="CN11_64" x="-29.21" y="-43.81" drill="1.02"/>
<pad name="CN11_65" x="-31.75" y="-46.35" drill="1.02"/>
<pad name="CN11_66" x="-29.21" y="-46.35" drill="1.02"/>
<pad name="CN11_67" x="-31.75" y="-48.89" drill="1.02"/>
<pad name="CN11_68" x="-29.21" y="-48.89" drill="1.02"/>
<pad name="CN11_69" x="-31.75" y="-51.43" drill="1.02"/>
<pad name="CN11_70" x="-29.21" y="-51.43" drill="1.02"/>
<pad name="CN12_1" x="29.21" y="34.91" drill="1.02" shape="square"/>
<pad name="CN12_2" x="31.75" y="34.91" drill="1.02"/>
<pad name="CN8_1" x="-24.13" y="24.77" drill="1.02" shape="square"/>
<pad name="CN8_2" x="-21.59" y="24.77" drill="1.02"/>
<pad name="CN8_3" x="-24.13" y="22.23" drill="1.02"/>
<pad name="CN8_4" x="-21.59" y="22.23" drill="1.02"/>
<pad name="CN8_5" x="-24.13" y="19.69" drill="1.02"/>
<pad name="CN8_6" x="-21.59" y="19.69" drill="1.02"/>
<pad name="CN8_7" x="-24.13" y="17.15" drill="1.02"/>
<pad name="CN8_8" x="-21.59" y="17.15" drill="1.02"/>
<pad name="CN8_9" x="-24.13" y="14.61" drill="1.02"/>
<pad name="CN8_10" x="-21.59" y="14.61" drill="1.02"/>
<pad name="CN8_11" x="-24.13" y="12.07" drill="1.02"/>
<pad name="CN8_12" x="-21.59" y="12.07" drill="1.02"/>
<pad name="CN8_13" x="-24.13" y="9.53" drill="1.02"/>
<pad name="CN8_14" x="-21.59" y="9.53" drill="1.02"/>
<pad name="CN8_15" x="-24.13" y="6.99" drill="1.02"/>
<pad name="CN8_16" x="-21.59" y="6.99" drill="1.02"/>
<pad name="CN9_1" x="-24.13" y="1.91" drill="1.02" shape="square"/>
<pad name="CN9_2" x="-21.59" y="1.91" drill="1.02"/>
<pad name="CN9_3" x="-24.13" y="-0.63" drill="1.02"/>
<pad name="CN9_4" x="-21.59" y="-0.63" drill="1.02"/>
<pad name="CN9_5" x="-24.13" y="-3.17" drill="1.02"/>
<pad name="CN9_6" x="-21.59" y="-3.17" drill="1.02"/>
<pad name="CN9_7" x="-24.13" y="-5.71" drill="1.02"/>
<pad name="CN9_8" x="-21.59" y="-5.71" drill="1.02"/>
<pad name="CN9_9" x="-24.13" y="-8.25" drill="1.02"/>
<pad name="CN9_10" x="-21.59" y="-8.25" drill="1.02"/>
<pad name="CN9_11" x="-24.13" y="-10.79" drill="1.02"/>
<pad name="CN9_12" x="-21.59" y="-10.79" drill="1.02"/>
<pad name="CN9_13" x="-24.13" y="-13.33" drill="1.02"/>
<pad name="CN9_14" x="-21.59" y="-13.33" drill="1.02"/>
<pad name="CN9_15" x="-24.13" y="-15.87" drill="1.02"/>
<pad name="CN9_16" x="-21.59" y="-15.87" drill="1.02"/>
<pad name="CN9_17" x="-24.13" y="-18.41" drill="1.02"/>
<pad name="CN9_18" x="-21.59" y="-18.41" drill="1.02"/>
<pad name="CN9_19" x="-24.13" y="-20.95" drill="1.02"/>
<pad name="CN9_20" x="-21.59" y="-20.95" drill="1.02"/>
<pad name="CN9_21" x="-24.13" y="-23.49" drill="1.02"/>
<pad name="CN9_22" x="-21.59" y="-23.49" drill="1.02"/>
<pad name="CN9_23" x="-24.13" y="-26.03" drill="1.02"/>
<pad name="CN9_24" x="-21.59" y="-26.03" drill="1.02"/>
<pad name="CN9_25" x="-24.13" y="-28.57" drill="1.02"/>
<pad name="CN9_26" x="-21.59" y="-28.57" drill="1.02"/>
<pad name="CN9_27" x="-24.13" y="-31.11" drill="1.02"/>
<pad name="CN9_28" x="-21.59" y="-31.11" drill="1.02"/>
<hole x="-22.86" y="-37.46" drill="3.2"/>
<pad name="CN7_1" x="21.59" y="33.914" drill="1.02" shape="square"/>
<pad name="CN7_2" x="24.13" y="33.914" drill="1.02"/>
<pad name="CN10_1" x="21.59" y="6.99" drill="1.02" shape="square"/>
<pad name="CN10_2" x="24.13" y="6.99" drill="1.02"/>
<pad name="CN10_3" x="21.59" y="4.45" drill="1.02"/>
<pad name="CN10_4" x="24.13" y="4.45" drill="1.02"/>
<pad name="CN10_5" x="21.59" y="1.91" drill="1.02"/>
<pad name="CN10_6" x="24.13" y="1.91" drill="1.02"/>
<pad name="CN10_7" x="21.59" y="-0.63" drill="1.02"/>
<pad name="CN10_8" x="24.13" y="-0.63" drill="1.02"/>
<pad name="CN10_9" x="21.59" y="-3.17" drill="1.02"/>
<pad name="CN10_10" x="24.13" y="-3.17" drill="1.02"/>
<pad name="CN10_11" x="21.59" y="-5.71" drill="1.02"/>
<pad name="CN10_12" x="24.13" y="-5.71" drill="1.02"/>
<pad name="CN10_13" x="21.59" y="-8.25" drill="1.02"/>
<pad name="CN10_14" x="24.13" y="-8.25" drill="1.02"/>
<pad name="CN10_15" x="21.59" y="-10.79" drill="1.02"/>
<pad name="CN10_16" x="24.13" y="-10.79" drill="1.02"/>
<hole x="22.86" y="-37.46" drill="3.2"/>
<pad name="CN10_17" x="21.59" y="-13.33" drill="1.02"/>
<pad name="CN10_18" x="24.13" y="-13.33" drill="1.02"/>
<pad name="CN10_19" x="21.59" y="-15.87" drill="1.02"/>
<pad name="CN10_20" x="24.13" y="-15.87" drill="1.02"/>
<pad name="CN10_21" x="21.59" y="-18.41" drill="1.02"/>
<pad name="CN10_22" x="24.13" y="-18.41" drill="1.02"/>
<pad name="CN10_23" x="21.59" y="-20.95" drill="1.02"/>
<pad name="CN10_24" x="24.13" y="-20.95" drill="1.02"/>
<pad name="CN10_25" x="21.59" y="-23.49" drill="1.02"/>
<pad name="CN10_26" x="24.13" y="-23.49" drill="1.02"/>
<pad name="CN10_27" x="21.59" y="-26.03" drill="1.02"/>
<pad name="CN10_28" x="24.13" y="-26.03" drill="1.02"/>
<pad name="CN10_29" x="21.59" y="-28.57" drill="1.02"/>
<pad name="CN10_30" x="24.13" y="-28.57" drill="1.02"/>
<pad name="CN10_31" x="21.59" y="-31.11" drill="1.02"/>
<pad name="CN10_32" x="24.13" y="-31.11" drill="1.02"/>
<pad name="CN11_71" x="-31.75" y="-53.97" drill="1.02"/>
<pad name="CN11_72" x="-29.21" y="-53.97" drill="1.02"/>
<hole x="24.13" y="37.47" drill="3.2"/>
<hole x="8.89" y="-13.33" drill="3.2"/>
<hole x="-24.13" y="38.74" drill="3.2"/>
<pad name="CN7_3" x="21.59" y="31.374" drill="1.02"/>
<pad name="CN7_4" x="24.13" y="31.374" drill="1.02"/>
<pad name="CN7_5" x="21.59" y="28.834" drill="1.02"/>
<pad name="CN7_6" x="24.13" y="28.834" drill="1.02"/>
<pad name="CN7_7" x="21.59" y="26.294" drill="1.02"/>
<pad name="CN7_8" x="24.13" y="26.294" drill="1.02"/>
<pad name="CN7_9" x="21.59" y="23.754" drill="1.02"/>
<pad name="CN7_10" x="24.13" y="23.754" drill="1.02"/>
<pad name="CN7_11" x="21.59" y="21.214" drill="1.02"/>
<pad name="CN7_12" x="24.13" y="21.214" drill="1.02"/>
<pad name="CN7_13" x="21.59" y="18.674" drill="1.02"/>
<pad name="CN7_14" x="24.13" y="18.674" drill="1.02"/>
<pad name="CN7_15" x="21.59" y="16.134" drill="1.02"/>
<pad name="CN7_16" x="24.13" y="16.134" drill="1.02"/>
<pad name="CN7_17" x="21.59" y="13.594" drill="1.02"/>
<pad name="CN7_18" x="24.13" y="13.594" drill="1.02"/>
<pad name="CN7_19" x="21.59" y="11.054" drill="1.02"/>
<pad name="CN7_20" x="24.13" y="11.054" drill="1.02"/>
<pad name="CN9_29" x="-24.13" y="-33.65" drill="1.02"/>
<pad name="CN9_30" x="-21.59" y="-33.65" drill="1.02"/>
<pad name="CN10_33" x="21.59" y="-33.65" drill="1.02"/>
<pad name="CN10_34" x="24.13" y="-33.65" drill="1.02"/>
<pad name="CN12_3" x="29.21" y="32.37" drill="1.02"/>
<pad name="CN12_4" x="31.75" y="32.37" drill="1.02"/>
<pad name="CN12_5" x="29.21" y="29.83" drill="1.02"/>
<pad name="CN12_6" x="31.75" y="29.83" drill="1.02"/>
<pad name="CN12_7" x="29.21" y="27.29" drill="1.02"/>
<pad name="CN12_8" x="31.75" y="27.29" drill="1.02"/>
<pad name="CN12_9" x="29.21" y="24.75" drill="1.02"/>
<pad name="CN12_10" x="31.75" y="24.75" drill="1.02"/>
<pad name="CN12_11" x="29.21" y="22.21" drill="1.02"/>
<pad name="CN12_12" x="31.75" y="22.21" drill="1.02"/>
<pad name="CN12_13" x="29.21" y="19.67" drill="1.02"/>
<pad name="CN12_14" x="31.75" y="19.67" drill="1.02"/>
<pad name="CN12_15" x="29.21" y="17.13" drill="1.02"/>
<pad name="CN12_16" x="31.75" y="17.13" drill="1.02"/>
<pad name="CN12_17" x="29.21" y="14.59" drill="1.02"/>
<pad name="CN12_18" x="31.75" y="14.59" drill="1.02"/>
<pad name="CN12_19" x="29.21" y="12.05" drill="1.02"/>
<pad name="CN12_20" x="31.75" y="12.05" drill="1.02"/>
<pad name="CN12_21" x="29.21" y="9.51" drill="1.02"/>
<pad name="CN12_22" x="31.75" y="9.51" drill="1.02"/>
<pad name="CN12_23" x="29.21" y="6.97" drill="1.02"/>
<pad name="CN12_24" x="31.75" y="6.97" drill="1.02"/>
<pad name="CN12_25" x="29.21" y="4.43" drill="1.02"/>
<pad name="CN12_26" x="31.75" y="4.43" drill="1.02"/>
<pad name="CN12_27" x="29.21" y="1.89" drill="1.02"/>
<pad name="CN12_28" x="31.75" y="1.89" drill="1.02"/>
<pad name="CN12_29" x="29.21" y="-0.65" drill="1.02"/>
<pad name="CN12_30" x="31.75" y="-0.65" drill="1.02"/>
<pad name="CN12_31" x="29.21" y="-3.19" drill="1.02"/>
<pad name="CN12_32" x="31.75" y="-3.19" drill="1.02"/>
<pad name="CN12_33" x="29.21" y="-5.73" drill="1.02"/>
<pad name="CN12_34" x="31.75" y="-5.73" drill="1.02"/>
<pad name="CN12_35" x="29.21" y="-8.27" drill="1.02"/>
<pad name="CN12_36" x="31.75" y="-8.27" drill="1.02"/>
<pad name="CN12_37" x="29.21" y="-10.81" drill="1.02"/>
<pad name="CN12_38" x="31.75" y="-10.81" drill="1.02"/>
<pad name="CN12_39" x="29.21" y="-13.35" drill="1.02"/>
<pad name="CN12_40" x="31.75" y="-13.35" drill="1.02"/>
<pad name="CN12_41" x="29.21" y="-15.89" drill="1.02"/>
<pad name="CN12_42" x="31.75" y="-15.89" drill="1.02"/>
<pad name="CN12_43" x="29.21" y="-18.43" drill="1.02"/>
<pad name="CN12_44" x="31.75" y="-18.43" drill="1.02"/>
<pad name="CN12_45" x="29.21" y="-20.97" drill="1.02"/>
<pad name="CN12_46" x="31.75" y="-20.97" drill="1.02"/>
<pad name="CN12_47" x="29.21" y="-23.51" drill="1.02"/>
<pad name="CN12_48" x="31.75" y="-23.51" drill="1.02"/>
<pad name="CN12_49" x="29.21" y="-26.05" drill="1.02"/>
<pad name="CN12_50" x="31.75" y="-26.05" drill="1.02"/>
<pad name="CN12_51" x="29.21" y="-28.59" drill="1.02"/>
<pad name="CN12_52" x="31.75" y="-28.59" drill="1.02"/>
<pad name="CN12_53" x="29.21" y="-31.13" drill="1.02"/>
<pad name="CN12_54" x="31.75" y="-31.13" drill="1.02"/>
<pad name="CN12_55" x="29.21" y="-33.67" drill="1.02"/>
<pad name="CN12_56" x="31.75" y="-33.67" drill="1.02"/>
<pad name="CN12_57" x="29.21" y="-36.21" drill="1.02"/>
<pad name="CN12_58" x="31.75" y="-36.21" drill="1.02"/>
<pad name="CN12_59" x="29.21" y="-38.75" drill="1.02"/>
<pad name="CN12_60" x="31.75" y="-38.75" drill="1.02"/>
<pad name="CN12_61" x="29.21" y="-41.29" drill="1.02"/>
<pad name="CN12_62" x="31.75" y="-41.29" drill="1.02"/>
<pad name="CN12_63" x="29.21" y="-43.83" drill="1.02"/>
<pad name="CN12_64" x="31.75" y="-43.83" drill="1.02"/>
<pad name="CN12_65" x="29.21" y="-46.37" drill="1.02"/>
<pad name="CN12_66" x="31.75" y="-46.37" drill="1.02"/>
<pad name="CN12_67" x="29.21" y="-48.91" drill="1.02"/>
<pad name="CN12_68" x="31.75" y="-48.91" drill="1.02"/>
<pad name="CN12_69" x="29.21" y="-51.45" drill="1.02"/>
<pad name="CN12_70" x="31.75" y="-51.45" drill="1.02"/>
<pad name="CN12_71" x="29.21" y="-53.99" drill="1.02"/>
<pad name="CN12_72" x="31.75" y="-53.99" drill="1.02"/>
</package>
</packages>
<symbols>
<symbol name="NUCLEO-F746ZG_CN11">
<wire x1="-12.7" y1="53.34" x2="-12.7" y2="-55.88" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-55.88" x2="12.7" y2="-55.88" width="0.254" layer="94"/>
<wire x1="12.7" y1="-55.88" x2="12.7" y2="53.34" width="0.254" layer="94"/>
<wire x1="12.7" y1="53.34" x2="-12.7" y2="53.34" width="0.254" layer="94"/>
<text x="-12.7" y="57.15" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="-57.15" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-12.7" y="54.102" size="1.778" layer="97">CN11</text>
<pin name="PC10" x="-17.78" y="-10.16" visible="pin" length="middle"/>
<pin name="PC11" x="-17.78" y="-12.7" visible="pin" length="middle"/>
<pin name="PC12" x="-17.78" y="-15.24" visible="pin" length="middle"/>
<pin name="PD2" x="-17.78" y="-33.02" visible="pin" length="middle"/>
<pin name="VDD_CN11" x="17.78" y="40.64" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="E5V_CN11" x="17.78" y="45.72" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="BOOT0" x="-17.78" y="33.02" visible="pin" length="middle"/>
<pin name="GND_CN11" x="17.78" y="-53.34" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PF6" x="17.78" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="PF7" x="17.78" y="-2.54" visible="pin" length="middle" rot="R180"/>
<pin name="IOREF_CN11" x="17.78" y="33.02" visible="pin" length="middle" rot="R180"/>
<pin name="PA13" x="-17.78" y="17.78" visible="pin" length="middle"/>
<pin name="RESET_CN11" x="-17.78" y="30.48" visible="pin" length="middle"/>
<pin name="PA14" x="-17.78" y="15.24" visible="pin" length="middle"/>
<pin name="+3V3_CN11" x="17.78" y="50.8" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PA15" x="-17.78" y="12.7" visible="pin" length="middle"/>
<pin name="+5V_CN11" x="17.78" y="48.26" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PB7" x="-17.78" y="5.08" visible="pin" length="middle"/>
<pin name="PC13" x="-17.78" y="-17.78" visible="pin" length="middle"/>
<pin name="VIN_CN11" x="17.78" y="38.1" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PC14" x="-17.78" y="-20.32" visible="pin" length="middle"/>
<pin name="PC15" x="-17.78" y="-22.86" visible="pin" length="middle"/>
<pin name="PA0" x="-17.78" y="25.4" visible="pin" length="middle"/>
<pin name="PH0" x="17.78" y="-40.64" visible="pin" length="middle" rot="R180"/>
<pin name="PA1" x="-17.78" y="22.86" visible="pin" length="middle"/>
<pin name="PH1" x="17.78" y="-43.18" visible="pin" length="middle" rot="R180"/>
<pin name="PA4" x="-17.78" y="20.32" visible="pin" length="middle"/>
<pin name="VBAT_CN11" x="17.78" y="43.18" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PB0" x="-17.78" y="7.62" visible="pin" length="middle"/>
<pin name="PC2" x="-17.78" y="-5.08" visible="pin" length="middle"/>
<pin name="PC1" x="-17.78" y="-2.54" visible="pin" length="middle"/>
<pin name="PC3" x="-17.78" y="-7.62" visible="pin" length="middle"/>
<pin name="PC0" x="-17.78" y="0" visible="pin" length="middle"/>
<pin name="PD4" x="-17.78" y="-38.1" visible="pin" length="middle"/>
<pin name="PD3" x="-17.78" y="-35.56" visible="pin" length="middle"/>
<pin name="PD5" x="-17.78" y="-40.64" visible="pin" length="middle"/>
<pin name="PG2" x="17.78" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="PD6" x="-17.78" y="-43.18" visible="pin" length="middle"/>
<pin name="PG3" x="17.78" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="PD7" x="-17.78" y="-45.72" visible="pin" length="middle"/>
<pin name="PE2" x="17.78" y="22.86" visible="pin" length="middle" rot="R180"/>
<pin name="PE3" x="17.78" y="20.32" visible="pin" length="middle" rot="R180"/>
<pin name="PE4" x="17.78" y="17.78" visible="pin" length="middle" rot="R180"/>
<pin name="PE5" x="17.78" y="15.24" visible="pin" length="middle" rot="R180"/>
<pin name="PF1" x="17.78" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="PF2" x="17.78" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="PF0" x="17.78" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="PF8" x="17.78" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="PD1" x="-17.78" y="-30.48" visible="pin" length="middle"/>
<pin name="PF9" x="17.78" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="PD0" x="-17.78" y="-27.94" visible="pin" length="middle"/>
<pin name="PG1" x="17.78" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="PG0" x="17.78" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="PE1" x="17.78" y="25.4" visible="pin" length="middle" rot="R180"/>
<pin name="PE6" x="17.78" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="PG9" x="17.78" y="-22.86" visible="pin" length="middle" rot="R180"/>
<pin name="PG15" x="17.78" y="-35.56" visible="pin" length="middle" rot="R180"/>
<pin name="PG12" x="17.78" y="-30.48" visible="pin" length="middle" rot="R180"/>
<pin name="PG10" x="17.78" y="-25.4" visible="pin" length="middle" rot="R180"/>
<pin name="PG13" x="17.78" y="-33.02" visible="pin" length="middle" rot="R180"/>
<pin name="PD9" x="-17.78" y="-48.26" visible="pin" length="middle"/>
<pin name="PG11" x="17.78" y="-27.94" visible="pin" length="middle" rot="R180"/>
</symbol>
<symbol name="NUCLEO-F746ZG_CN12">
<wire x1="-17.78" y1="53.34" x2="-17.78" y2="-53.34" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-53.34" x2="17.78" y2="-53.34" width="0.254" layer="94"/>
<wire x1="17.78" y1="-53.34" x2="17.78" y2="53.34" width="0.254" layer="94"/>
<wire x1="17.78" y1="53.34" x2="-17.78" y2="53.34" width="0.254" layer="94"/>
<text x="-17.78" y="57.15" size="1.778" layer="95">&gt;NAME</text>
<text x="-17.78" y="-54.61" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-17.78" y="54.102" size="1.778" layer="97">CN12</text>
<pin name="PC9" x="-22.86" y="-35.56" visible="pin" length="middle"/>
<pin name="PC8" x="-22.86" y="-33.02" visible="pin" length="middle"/>
<pin name="PB8" x="-22.86" y="0" visible="pin" length="middle"/>
<pin name="PC6" x="-22.86" y="-27.94" visible="pin" length="middle"/>
<pin name="PB9" x="-22.86" y="-2.54" visible="pin" length="middle"/>
<pin name="PC5" x="-22.86" y="-25.4" visible="pin" length="middle"/>
<pin name="AVDD_CN12" x="22.86" y="50.8" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="U5V" x="22.86" y="48.26" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="GND_CN12" x="22.86" y="-50.8" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PD8" x="22.86" y="43.18" visible="pin" length="middle" rot="R180"/>
<pin name="PA5" x="-22.86" y="38.1" visible="pin" length="middle"/>
<pin name="PA12" x="-22.86" y="20.32" visible="pin" length="middle"/>
<pin name="PA6" x="-22.86" y="35.56" visible="pin" length="middle"/>
<pin name="PA11" x="-22.86" y="22.86" visible="pin" length="middle"/>
<pin name="PA7" x="-22.86" y="33.02" visible="pin" length="middle"/>
<pin name="PB12" x="-22.86" y="-10.16" visible="pin" length="middle"/>
<pin name="PB6" x="-22.86" y="2.54" visible="pin" length="middle"/>
<pin name="PB11" x="-22.86" y="-7.62" visible="pin" length="middle"/>
<pin name="PC7" x="-22.86" y="-30.48" visible="pin" length="middle"/>
<pin name="PA9" x="-22.86" y="27.94" visible="pin" length="middle"/>
<pin name="PB2" x="-22.86" y="12.7" visible="pin" length="middle"/>
<pin name="PA8" x="-22.86" y="30.48" visible="pin" length="middle"/>
<pin name="PB1" x="-22.86" y="15.24" visible="pin" length="middle"/>
<pin name="PB10" x="-22.86" y="-5.08" visible="pin" length="middle"/>
<pin name="PB15" x="-22.86" y="-17.78" visible="pin" length="middle"/>
<pin name="PB4" x="-22.86" y="7.62" visible="pin" length="middle"/>
<pin name="PB14" x="-22.86" y="-15.24" visible="pin" length="middle"/>
<pin name="PB5" x="-22.86" y="5.08" visible="pin" length="middle"/>
<pin name="PB13" x="-22.86" y="-12.7" visible="pin" length="middle"/>
<pin name="PB3" x="-22.86" y="10.16" visible="pin" length="middle"/>
<pin name="AGND_CN12" x="22.86" y="-48.26" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="PA10" x="-22.86" y="25.4" visible="pin" length="middle"/>
<pin name="PC4" x="-22.86" y="-22.86" visible="pin" length="middle"/>
<pin name="PA2" x="-22.86" y="43.18" visible="pin" length="middle"/>
<pin name="PF5" x="22.86" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="PA3" x="-22.86" y="40.64" visible="pin" length="middle"/>
<pin name="PF4" x="22.86" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="PE8" x="22.86" y="17.78" visible="pin" length="middle" rot="R180"/>
<pin name="PD13" x="22.86" y="33.02" visible="pin" length="middle" rot="R180"/>
<pin name="PF10" x="22.86" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="PD12" x="22.86" y="35.56" visible="pin" length="middle" rot="R180"/>
<pin name="PE7" x="22.86" y="20.32" visible="pin" length="middle" rot="R180"/>
<pin name="PD11" x="22.86" y="38.1" visible="pin" length="middle" rot="R180"/>
<pin name="PD14" x="22.86" y="30.48" visible="pin" length="middle" rot="R180"/>
<pin name="PE10" x="22.86" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="PD15" x="22.86" y="27.94" visible="pin" length="middle" rot="R180"/>
<pin name="PE12" x="22.86" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="PF14" x="22.86" y="-22.86" visible="pin" length="middle" rot="R180"/>
<pin name="PE14" x="22.86" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="PE9" x="22.86" y="15.24" visible="pin" length="middle" rot="R180"/>
<pin name="PE15" x="22.86" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="PE13" x="22.86" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="PE11" x="22.86" y="10.16" visible="pin" length="middle" rot="R180"/>
<pin name="PF13" x="22.86" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="PF3" x="22.86" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="PF12" x="22.86" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="PF15" x="22.86" y="-25.4" visible="pin" length="middle" rot="R180"/>
<pin name="PG14" x="22.86" y="-43.18" visible="pin" length="middle" rot="R180"/>
<pin name="PF11" x="22.86" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="PE0" x="22.86" y="22.86" visible="pin" length="middle" rot="R180"/>
<pin name="PD10" x="22.86" y="40.64" visible="pin" length="middle" rot="R180"/>
<pin name="PG8" x="22.86" y="-40.64" visible="pin" length="middle" rot="R180"/>
<pin name="PG7" x="22.86" y="-38.1" visible="pin" length="middle" rot="R180"/>
<pin name="PG5" x="22.86" y="-33.02" visible="pin" length="middle" rot="R180"/>
<pin name="PG4" x="22.86" y="-30.48" visible="pin" length="middle" rot="R180"/>
<pin name="PG6" x="22.86" y="-35.56" visible="pin" length="middle" rot="R180"/>
</symbol>
<symbol name="NUCLEO-F746ZG_CN8">
<wire x1="-27.94" y1="17.78" x2="-27.94" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-27.94" y1="-17.78" x2="27.94" y2="-17.78" width="0.254" layer="94"/>
<wire x1="27.94" y1="-17.78" x2="27.94" y2="17.78" width="0.254" layer="94"/>
<wire x1="27.94" y1="17.78" x2="-27.94" y2="17.78" width="0.254" layer="94"/>
<text x="-27.94" y="21.59" size="1.778" layer="95">&gt;NAME</text>
<text x="-27.94" y="-19.05" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-27.94" y="18.542" size="1.778" layer="97">CN8</text>
<pin name="D43/SDMMC_D0" x="-33.02" y="0" visible="pin" length="middle"/>
<pin name="IOREF_CN8" x="33.02" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="D44/SDMMC_D1/I2S_A_CKIN" x="-33.02" y="-2.54" visible="pin" length="middle"/>
<pin name="RESET_CN8" x="-33.02" y="5.08" visible="pin" length="middle"/>
<pin name="D45/SDMMC_D2" x="-33.02" y="-5.08" visible="pin" length="middle"/>
<pin name="+3V3_CN8" x="33.02" y="10.16" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D46/SDMMC_D3" x="-33.02" y="-7.62" visible="pin" length="middle"/>
<pin name="+5V_CN8" x="33.02" y="12.7" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D47/SDMMC_CK" x="-33.02" y="-10.16" visible="pin" length="middle"/>
<pin name="GND_CN8" x="33.02" y="-15.24" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D48/SDMMC_CMD" x="-33.02" y="-12.7" visible="pin" length="middle"/>
<pin name="D49/IO" x="33.02" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="VIN_CN8" x="33.02" y="15.24" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D50/IO" x="33.02" y="-2.54" visible="pin" length="middle" rot="R180"/>
</symbol>
<symbol name="NUCLEO-F746ZG_CN9">
<wire x1="-25.4" y1="25.4" x2="-25.4" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-25.4" x2="25.4" y2="-25.4" width="0.254" layer="94"/>
<wire x1="25.4" y1="-25.4" x2="25.4" y2="25.4" width="0.254" layer="94"/>
<wire x1="25.4" y1="25.4" x2="-25.4" y2="25.4" width="0.254" layer="94"/>
<text x="-25.4" y="29.21" size="1.778" layer="95">&gt;NAME</text>
<text x="-25.4" y="-26.67" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-25.4" y="26.162" size="1.778" layer="97">CN9</text>
<pin name="A0/ADC123_IN3" x="-30.48" y="22.86" visible="pin" length="middle" direction="in"/>
<pin name="D51/USART_B_SCLK" x="-30.48" y="5.08" visible="pin" length="middle" function="clk"/>
<pin name="A1/ADC123_IN10" x="-30.48" y="20.32" visible="pin" length="middle" direction="in"/>
<pin name="D52/USART_B_RX" x="-30.48" y="2.54" visible="pin" length="middle"/>
<pin name="A2/ADC123_IN13" x="-30.48" y="17.78" visible="pin" length="middle" direction="in"/>
<pin name="D53/USART_B_TX" x="-30.48" y="0" visible="pin" length="middle"/>
<pin name="A3/ADC3_IN9" x="-30.48" y="15.24" visible="pin" length="middle" direction="in"/>
<pin name="D54/USART_B_RTS" x="-30.48" y="-2.54" visible="pin" length="middle"/>
<pin name="A4/ADC3_IN15/I2C1_SDA" x="-30.48" y="12.7" visible="pin" length="middle" direction="in"/>
<pin name="D55/USART_B_CTS" x="-30.48" y="-5.08" visible="pin" length="middle"/>
<pin name="A5/ADC3_IN8/I2C1_SCL" x="-30.48" y="10.16" visible="pin" length="middle" direction="in"/>
<pin name="GND_CN9" x="30.48" y="-22.86" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D72/NC" x="30.48" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="D56/SAI_A_MCLK" x="-30.48" y="-10.16" visible="pin" length="middle" function="clk"/>
<pin name="D71/IO" x="30.48" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="D57/SAI_A_FS" x="-30.48" y="-12.7" visible="pin" length="middle"/>
<pin name="D70/I2C_B_SMBA" x="30.48" y="17.78" visible="pin" length="middle" rot="R180"/>
<pin name="D58/SAI_A_SCK" x="-30.48" y="-15.24" visible="pin" length="middle" function="clk"/>
<pin name="D69/I2C_B_SCL" x="30.48" y="20.32" visible="pin" length="middle" function="clk" rot="R180"/>
<pin name="D59/SAI_A_SD" x="-30.48" y="-17.78" visible="pin" length="middle"/>
<pin name="D68/I2C_B_SDA" x="30.48" y="22.86" visible="pin" length="middle" rot="R180"/>
<pin name="D60/SAI_B_SD" x="30.48" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="D61/SAI_B_SCK" x="30.48" y="-15.24" visible="pin" length="middle" function="clk" rot="R180"/>
<pin name="D67/CAN_RX" x="30.48" y="10.16" visible="pin" length="middle" direction="in" rot="R180"/>
<pin name="D62/SAI_B_MCLK" x="30.48" y="-10.16" visible="pin" length="middle" function="clk" rot="R180"/>
<pin name="D66/CAN_TX" x="30.48" y="12.7" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="D63/SAI_B_FS" x="30.48" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D65/IO" x="30.48" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="D64/IO" x="30.48" y="5.08" visible="pin" length="middle" rot="R180"/>
</symbol>
<symbol name="NUCLEO-F746ZG_CN7">
<wire x1="-33.02" y1="20.32" x2="-33.02" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-33.02" y1="-20.32" x2="33.02" y2="-20.32" width="0.254" layer="94"/>
<wire x1="33.02" y1="-20.32" x2="33.02" y2="20.32" width="0.254" layer="94"/>
<wire x1="33.02" y1="20.32" x2="-33.02" y2="20.32" width="0.254" layer="94"/>
<text x="-33.02" y="24.13" size="1.778" layer="95">&gt;NAME</text>
<text x="-33.02" y="-21.59" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-33.02" y="21.082" size="1.778" layer="97">CN7</text>
<pin name="D16/I2S_A_MCK" x="-38.1" y="-12.7" visible="pin" length="middle"/>
<pin name="D15/I2C_A_SCL" x="-38.1" y="-10.16" visible="pin" length="middle"/>
<pin name="D17/I2S_A_SD" x="38.1" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D14/I2C_A_SDA" x="-38.1" y="-7.62" visible="pin" length="middle"/>
<pin name="D18/I2S_A_CK" x="38.1" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="AREF" x="38.1" y="17.78" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D19/I2S_A_WS" x="38.1" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="GND_CN7" x="38.1" y="-17.78" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D20/I2S_B_WS" x="38.1" y="-2.54" visible="pin" length="middle" rot="R180"/>
<pin name="D13/SPI_A_SCK" x="-38.1" y="-5.08" visible="pin" length="middle"/>
<pin name="D21/I2S_B_MCK" x="38.1" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="D12/SPI_A_MISO" x="-38.1" y="-2.54" visible="pin" length="middle"/>
<pin name="D22/I2S_B_SD/SPI_B_MOSI" x="38.1" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="D11/SPI_A_MOSI/TIM_E_PWM1" x="-38.1" y="0" visible="pin" length="middle"/>
<pin name="D23/I2S_B_CK/SPI_B_SCK" x="38.1" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="D10/SPI_A_CS/TIM_B_PWM3" x="-38.1" y="2.54" visible="pin" length="middle"/>
<pin name="D24/SPI_B_NSS" x="38.1" y="10.16" visible="pin" length="middle" rot="R180"/>
<pin name="D9/TIMER_B_PWM2" x="-38.1" y="10.16" visible="pin" length="middle"/>
<pin name="D25/SPI_B_MISO" x="38.1" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D8/IO" x="-38.1" y="12.7" visible="pin" length="middle"/>
</symbol>
<symbol name="NUCLEO-F746ZG_CN10">
<wire x1="-25.4" y1="30.48" x2="-25.4" y2="-30.48" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-30.48" x2="25.4" y2="-30.48" width="0.254" layer="94"/>
<wire x1="25.4" y1="-30.48" x2="25.4" y2="30.48" width="0.254" layer="94"/>
<wire x1="25.4" y1="30.48" x2="-25.4" y2="30.48" width="0.254" layer="94"/>
<text x="-25.4" y="34.29" size="1.778" layer="95">&gt;NAME</text>
<text x="-25.4" y="-31.75" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
<text x="-25.4" y="31.242" size="1.778" layer="97">CN10</text>
<pin name="AVDD_CN10" x="30.48" y="27.94" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D7/IO" x="30.48" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="AGND_CN10" x="30.48" y="-25.4" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D6/TIMER_A_PWM1" x="-30.48" y="5.08" visible="pin" length="middle"/>
<pin name="GND_CN10" x="30.48" y="-27.94" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="D5/TIMER_A_PWM2" x="-30.48" y="2.54" visible="pin" length="middle"/>
<pin name="A6/ADC_A_IN" x="-30.48" y="22.86" visible="pin" length="middle" direction="in"/>
<pin name="D4/IO" x="30.48" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="A7/ADC_B_IN" x="-30.48" y="20.32" visible="pin" length="middle" direction="in"/>
<pin name="D3/TIMER_A_PWM3" x="-30.48" y="0" visible="pin" length="middle"/>
<pin name="A8/ADC_C_IN" x="-30.48" y="17.78" visible="pin" length="middle" direction="in"/>
<pin name="D2/IO" x="30.48" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D26/QSPI_CS" x="-30.48" y="-5.08" visible="pin" length="middle"/>
<pin name="D1/USART_A_TX" x="-30.48" y="10.16" visible="pin" length="middle" direction="out"/>
<pin name="D27/QSPI_CLK" x="-30.48" y="-7.62" visible="pin" length="middle" function="clk"/>
<pin name="D0/USART_A_RX" x="-30.48" y="12.7" visible="pin" length="middle" direction="in"/>
<pin name="D42/TIMER_A_PWM1N" x="30.48" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="D28/QSPI_BK1_IO3" x="-30.48" y="-10.16" visible="pin" length="middle"/>
<pin name="D41/TIMER_A_ETR" x="30.48" y="15.24" visible="pin" length="middle" rot="R180"/>
<pin name="D29/QSPI_BK1_IO1" x="-30.48" y="-12.7" visible="pin" length="middle"/>
<pin name="D30/QSPI_BK1_IO0" x="-30.48" y="-15.24" visible="pin" length="middle"/>
<pin name="D40/TIMER_A_PWM2N" x="30.48" y="17.78" visible="pin" length="middle" rot="R180"/>
<pin name="D31/QSPI_BK1_IO2" x="-30.48" y="-17.78" visible="pin" length="middle"/>
<pin name="D39/TIMER_A_PWM3N" x="30.48" y="20.32" visible="pin" length="middle" rot="R180"/>
<pin name="D38/IO" x="30.48" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="D32/TIMER_C_PWM1" x="30.48" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="D37/TIMER_A_BKIN1" x="30.48" y="22.86" visible="pin" length="middle" rot="R180"/>
<pin name="D33/TIMER_D_PWM1" x="30.48" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="D36/TIMER_C_PWM2" x="30.48" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="D34/TIMER_B_ETR" x="30.48" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="D35/TIMER_C_PWM3" x="30.48" y="-2.54" visible="pin" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="NUCLEO-F746ZG" prefix="A">
<description>STM32 Nucleo-144 development board with STM32F746ZG MCU, supports Arduino, ST Zio and morpho connectivity &lt;a href="https://pricing.snapeda.com/parts/NUCLEO-F746ZG/STMicroelectronics/view-part?ref=eda"&gt;Check prices&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="NUCLEO-F746ZG_CN11" x="-167.64" y="0" swaplevel="1"/>
<gate name="G$2" symbol="NUCLEO-F746ZG_CN12" x="-104.14" y="0" swaplevel="2"/>
<gate name="G$3" symbol="NUCLEO-F746ZG_CN8" x="-38.1" y="-2.54" swaplevel="3"/>
<gate name="G$4" symbol="NUCLEO-F746ZG_CN9" x="40.64" y="-5.08" swaplevel="4"/>
<gate name="G$5" symbol="NUCLEO-F746ZG_CN7" x="127" y="-2.54" swaplevel="5"/>
<gate name="G$6" symbol="NUCLEO-F746ZG_CN10" x="210.82" y="-2.54" swaplevel="6"/>
</gates>
<devices>
<device name="" package="MODULE_NUCLEO-F746ZG">
<connects>
<connect gate="G$1" pin="+3V3_CN11" pad="CN11_16"/>
<connect gate="G$1" pin="+5V_CN11" pad="CN11_18"/>
<connect gate="G$1" pin="BOOT0" pad="CN11_7"/>
<connect gate="G$1" pin="E5V_CN11" pad="CN11_6"/>
<connect gate="G$1" pin="GND_CN11" pad="CN11_8 CN11_19 CN11_20 CN11_22 CN11_49 CN11_60 CN11_71 CN11_72"/>
<connect gate="G$1" pin="IOREF_CN11" pad="CN11_12"/>
<connect gate="G$1" pin="PA0" pad="CN11_28"/>
<connect gate="G$1" pin="PA1" pad="CN11_30"/>
<connect gate="G$1" pin="PA13" pad="CN11_13"/>
<connect gate="G$1" pin="PA14" pad="CN11_15"/>
<connect gate="G$1" pin="PA15" pad="CN11_17"/>
<connect gate="G$1" pin="PA4" pad="CN11_32"/>
<connect gate="G$1" pin="PB0" pad="CN11_34"/>
<connect gate="G$1" pin="PB7" pad="CN11_21"/>
<connect gate="G$1" pin="PC0" pad="CN11_38"/>
<connect gate="G$1" pin="PC1" pad="CN11_36"/>
<connect gate="G$1" pin="PC10" pad="CN11_1"/>
<connect gate="G$1" pin="PC11" pad="CN11_2"/>
<connect gate="G$1" pin="PC12" pad="CN11_3"/>
<connect gate="G$1" pin="PC13" pad="CN11_23"/>
<connect gate="G$1" pin="PC14" pad="CN11_25"/>
<connect gate="G$1" pin="PC15" pad="CN11_27"/>
<connect gate="G$1" pin="PC2" pad="CN11_35"/>
<connect gate="G$1" pin="PC3" pad="CN11_37"/>
<connect gate="G$1" pin="PD0" pad="CN11_57"/>
<connect gate="G$1" pin="PD1" pad="CN11_55"/>
<connect gate="G$1" pin="PD2" pad="CN11_4"/>
<connect gate="G$1" pin="PD3" pad="CN11_40"/>
<connect gate="G$1" pin="PD4" pad="CN11_39"/>
<connect gate="G$1" pin="PD5" pad="CN11_41"/>
<connect gate="G$1" pin="PD6" pad="CN11_43"/>
<connect gate="G$1" pin="PD7" pad="CN11_45"/>
<connect gate="G$1" pin="PD9" pad="CN11_69"/>
<connect gate="G$1" pin="PE1" pad="CN11_61"/>
<connect gate="G$1" pin="PE2" pad="CN11_46"/>
<connect gate="G$1" pin="PE3" pad="CN11_47"/>
<connect gate="G$1" pin="PE4" pad="CN11_48"/>
<connect gate="G$1" pin="PE5" pad="CN11_50"/>
<connect gate="G$1" pin="PE6" pad="CN11_62"/>
<connect gate="G$1" pin="PF0" pad="CN11_53"/>
<connect gate="G$1" pin="PF1" pad="CN11_51"/>
<connect gate="G$1" pin="PF2" pad="CN11_52"/>
<connect gate="G$1" pin="PF6" pad="CN11_9"/>
<connect gate="G$1" pin="PF7" pad="CN11_11"/>
<connect gate="G$1" pin="PF8" pad="CN11_54"/>
<connect gate="G$1" pin="PF9" pad="CN11_56"/>
<connect gate="G$1" pin="PG0" pad="CN11_59"/>
<connect gate="G$1" pin="PG1" pad="CN11_58"/>
<connect gate="G$1" pin="PG10" pad="CN11_66"/>
<connect gate="G$1" pin="PG11" pad="CN11_70"/>
<connect gate="G$1" pin="PG12" pad="CN11_65"/>
<connect gate="G$1" pin="PG13" pad="CN11_68"/>
<connect gate="G$1" pin="PG15" pad="CN11_64"/>
<connect gate="G$1" pin="PG2" pad="CN11_42"/>
<connect gate="G$1" pin="PG3" pad="CN11_44"/>
<connect gate="G$1" pin="PG9" pad="CN11_63"/>
<connect gate="G$1" pin="PH0" pad="CN11_29"/>
<connect gate="G$1" pin="PH1" pad="CN11_31"/>
<connect gate="G$1" pin="RESET_CN11" pad="CN11_14"/>
<connect gate="G$1" pin="VBAT_CN11" pad="CN11_33"/>
<connect gate="G$1" pin="VDD_CN11" pad="CN11_5"/>
<connect gate="G$1" pin="VIN_CN11" pad="CN11_24"/>
<connect gate="G$2" pin="AGND_CN12" pad="CN12_32"/>
<connect gate="G$2" pin="AVDD_CN12" pad="CN12_7"/>
<connect gate="G$2" pin="GND_CN12" pad="CN12_9 CN12_20 CN12_39 CN12_54 CN12_63 CN12_71 CN12_72"/>
<connect gate="G$2" pin="PA10" pad="CN12_33"/>
<connect gate="G$2" pin="PA11" pad="CN12_14"/>
<connect gate="G$2" pin="PA12" pad="CN12_12"/>
<connect gate="G$2" pin="PA2" pad="CN12_35"/>
<connect gate="G$2" pin="PA3" pad="CN12_37"/>
<connect gate="G$2" pin="PA5" pad="CN12_11"/>
<connect gate="G$2" pin="PA6" pad="CN12_13"/>
<connect gate="G$2" pin="PA7" pad="CN12_15"/>
<connect gate="G$2" pin="PA8" pad="CN12_23"/>
<connect gate="G$2" pin="PA9" pad="CN12_21"/>
<connect gate="G$2" pin="PB1" pad="CN12_24"/>
<connect gate="G$2" pin="PB10" pad="CN12_25"/>
<connect gate="G$2" pin="PB11" pad="CN12_18"/>
<connect gate="G$2" pin="PB12" pad="CN12_16"/>
<connect gate="G$2" pin="PB13" pad="CN12_30"/>
<connect gate="G$2" pin="PB14" pad="CN12_28"/>
<connect gate="G$2" pin="PB15" pad="CN12_26"/>
<connect gate="G$2" pin="PB2" pad="CN12_22"/>
<connect gate="G$2" pin="PB3" pad="CN12_31"/>
<connect gate="G$2" pin="PB4" pad="CN12_27"/>
<connect gate="G$2" pin="PB5" pad="CN12_29"/>
<connect gate="G$2" pin="PB6" pad="CN12_17"/>
<connect gate="G$2" pin="PB8" pad="CN12_3"/>
<connect gate="G$2" pin="PB9" pad="CN12_5"/>
<connect gate="G$2" pin="PC4" pad="CN12_34"/>
<connect gate="G$2" pin="PC5" pad="CN12_6"/>
<connect gate="G$2" pin="PC6" pad="CN12_4"/>
<connect gate="G$2" pin="PC7" pad="CN12_19"/>
<connect gate="G$2" pin="PC8" pad="CN12_2"/>
<connect gate="G$2" pin="PC9" pad="CN12_1"/>
<connect gate="G$2" pin="PD10" pad="CN12_65"/>
<connect gate="G$2" pin="PD11" pad="CN12_45"/>
<connect gate="G$2" pin="PD12" pad="CN12_43"/>
<connect gate="G$2" pin="PD13" pad="CN12_41"/>
<connect gate="G$2" pin="PD14" pad="CN12_46"/>
<connect gate="G$2" pin="PD15" pad="CN12_48"/>
<connect gate="G$2" pin="PD8" pad="CN12_10"/>
<connect gate="G$2" pin="PE0" pad="CN12_64"/>
<connect gate="G$2" pin="PE10" pad="CN12_47"/>
<connect gate="G$2" pin="PE11" pad="CN12_56"/>
<connect gate="G$2" pin="PE12" pad="CN12_49"/>
<connect gate="G$2" pin="PE13" pad="CN12_55"/>
<connect gate="G$2" pin="PE14" pad="CN12_51"/>
<connect gate="G$2" pin="PE15" pad="CN12_53"/>
<connect gate="G$2" pin="PE7" pad="CN12_44"/>
<connect gate="G$2" pin="PE8" pad="CN12_40"/>
<connect gate="G$2" pin="PE9" pad="CN12_52"/>
<connect gate="G$2" pin="PF10" pad="CN12_42"/>
<connect gate="G$2" pin="PF11" pad="CN12_62"/>
<connect gate="G$2" pin="PF12" pad="CN12_59"/>
<connect gate="G$2" pin="PF13" pad="CN12_57"/>
<connect gate="G$2" pin="PF14" pad="CN12_50"/>
<connect gate="G$2" pin="PF15" pad="CN12_60"/>
<connect gate="G$2" pin="PF3" pad="CN12_58"/>
<connect gate="G$2" pin="PF4" pad="CN12_38"/>
<connect gate="G$2" pin="PF5" pad="CN12_36"/>
<connect gate="G$2" pin="PG14" pad="CN12_61"/>
<connect gate="G$2" pin="PG4" pad="CN12_69"/>
<connect gate="G$2" pin="PG5" pad="CN12_68"/>
<connect gate="G$2" pin="PG6" pad="CN12_70"/>
<connect gate="G$2" pin="PG7" pad="CN12_67"/>
<connect gate="G$2" pin="PG8" pad="CN12_66"/>
<connect gate="G$2" pin="U5V" pad="CN12_8"/>
<connect gate="G$3" pin="+3V3_CN8" pad="CN8_7"/>
<connect gate="G$3" pin="+5V_CN8" pad="CN8_9"/>
<connect gate="G$3" pin="D43/SDMMC_D0" pad="CN8_2"/>
<connect gate="G$3" pin="D44/SDMMC_D1/I2S_A_CKIN" pad="CN8_4"/>
<connect gate="G$3" pin="D45/SDMMC_D2" pad="CN8_6"/>
<connect gate="G$3" pin="D46/SDMMC_D3" pad="CN8_8"/>
<connect gate="G$3" pin="D47/SDMMC_CK" pad="CN8_10"/>
<connect gate="G$3" pin="D48/SDMMC_CMD" pad="CN8_12"/>
<connect gate="G$3" pin="D49/IO" pad="CN8_14"/>
<connect gate="G$3" pin="D50/IO" pad="CN8_16"/>
<connect gate="G$3" pin="GND_CN8" pad="CN8_11 CN8_13"/>
<connect gate="G$3" pin="IOREF_CN8" pad="CN8_3"/>
<connect gate="G$3" pin="RESET_CN8" pad="CN8_5"/>
<connect gate="G$3" pin="VIN_CN8" pad="CN8_15"/>
<connect gate="G$4" pin="A0/ADC123_IN3" pad="CN9_1"/>
<connect gate="G$4" pin="A1/ADC123_IN10" pad="CN9_3"/>
<connect gate="G$4" pin="A2/ADC123_IN13" pad="CN9_5"/>
<connect gate="G$4" pin="A3/ADC3_IN9" pad="CN9_7"/>
<connect gate="G$4" pin="A4/ADC3_IN15/I2C1_SDA" pad="CN9_9"/>
<connect gate="G$4" pin="A5/ADC3_IN8/I2C1_SCL" pad="CN9_11"/>
<connect gate="G$4" pin="D51/USART_B_SCLK" pad="CN9_2"/>
<connect gate="G$4" pin="D52/USART_B_RX" pad="CN9_4"/>
<connect gate="G$4" pin="D53/USART_B_TX" pad="CN9_6"/>
<connect gate="G$4" pin="D54/USART_B_RTS" pad="CN9_8"/>
<connect gate="G$4" pin="D55/USART_B_CTS" pad="CN9_10"/>
<connect gate="G$4" pin="D56/SAI_A_MCLK" pad="CN9_14"/>
<connect gate="G$4" pin="D57/SAI_A_FS" pad="CN9_16"/>
<connect gate="G$4" pin="D58/SAI_A_SCK" pad="CN9_18"/>
<connect gate="G$4" pin="D59/SAI_A_SD" pad="CN9_20"/>
<connect gate="G$4" pin="D60/SAI_B_SD" pad="CN9_22"/>
<connect gate="G$4" pin="D61/SAI_B_SCK" pad="CN9_24"/>
<connect gate="G$4" pin="D62/SAI_B_MCLK" pad="CN9_26"/>
<connect gate="G$4" pin="D63/SAI_B_FS" pad="CN9_28"/>
<connect gate="G$4" pin="D64/IO" pad="CN9_30"/>
<connect gate="G$4" pin="D65/IO" pad="CN9_29"/>
<connect gate="G$4" pin="D66/CAN_TX" pad="CN9_27"/>
<connect gate="G$4" pin="D67/CAN_RX" pad="CN9_25"/>
<connect gate="G$4" pin="D68/I2C_B_SDA" pad="CN9_21"/>
<connect gate="G$4" pin="D69/I2C_B_SCL" pad="CN9_19"/>
<connect gate="G$4" pin="D70/I2C_B_SMBA" pad="CN9_17"/>
<connect gate="G$4" pin="D71/IO" pad="CN9_15"/>
<connect gate="G$4" pin="D72/NC" pad="CN9_13"/>
<connect gate="G$4" pin="GND_CN9" pad="CN9_12 CN9_23"/>
<connect gate="G$5" pin="AREF" pad="CN7_6"/>
<connect gate="G$5" pin="D10/SPI_A_CS/TIM_B_PWM3" pad="CN7_16"/>
<connect gate="G$5" pin="D11/SPI_A_MOSI/TIM_E_PWM1" pad="CN7_14"/>
<connect gate="G$5" pin="D12/SPI_A_MISO" pad="CN7_12"/>
<connect gate="G$5" pin="D13/SPI_A_SCK" pad="CN7_10"/>
<connect gate="G$5" pin="D14/I2C_A_SDA" pad="CN7_4"/>
<connect gate="G$5" pin="D15/I2C_A_SCL" pad="CN7_2"/>
<connect gate="G$5" pin="D16/I2S_A_MCK" pad="CN7_1"/>
<connect gate="G$5" pin="D17/I2S_A_SD" pad="CN7_3"/>
<connect gate="G$5" pin="D18/I2S_A_CK" pad="CN7_5"/>
<connect gate="G$5" pin="D19/I2S_A_WS" pad="CN7_7"/>
<connect gate="G$5" pin="D20/I2S_B_WS" pad="CN7_9"/>
<connect gate="G$5" pin="D21/I2S_B_MCK" pad="CN7_11"/>
<connect gate="G$5" pin="D22/I2S_B_SD/SPI_B_MOSI" pad="CN7_13"/>
<connect gate="G$5" pin="D23/I2S_B_CK/SPI_B_SCK" pad="CN7_15"/>
<connect gate="G$5" pin="D24/SPI_B_NSS" pad="CN7_17"/>
<connect gate="G$5" pin="D25/SPI_B_MISO" pad="CN7_19"/>
<connect gate="G$5" pin="D8/IO" pad="CN7_20"/>
<connect gate="G$5" pin="D9/TIMER_B_PWM2" pad="CN7_18"/>
<connect gate="G$5" pin="GND_CN7" pad="CN7_8"/>
<connect gate="G$6" pin="A6/ADC_A_IN" pad="CN10_7"/>
<connect gate="G$6" pin="A7/ADC_B_IN" pad="CN10_9"/>
<connect gate="G$6" pin="A8/ADC_C_IN" pad="CN10_11"/>
<connect gate="G$6" pin="AGND_CN10" pad="CN10_3"/>
<connect gate="G$6" pin="AVDD_CN10" pad="CN10_1"/>
<connect gate="G$6" pin="D0/USART_A_RX" pad="CN10_16"/>
<connect gate="G$6" pin="D1/USART_A_TX" pad="CN10_14"/>
<connect gate="G$6" pin="D2/IO" pad="CN10_12"/>
<connect gate="G$6" pin="D26/QSPI_CS" pad="CN10_13"/>
<connect gate="G$6" pin="D27/QSPI_CLK" pad="CN10_15"/>
<connect gate="G$6" pin="D28/QSPI_BK1_IO3" pad="CN10_19"/>
<connect gate="G$6" pin="D29/QSPI_BK1_IO1" pad="CN10_21"/>
<connect gate="G$6" pin="D3/TIMER_A_PWM3" pad="CN10_10"/>
<connect gate="G$6" pin="D30/QSPI_BK1_IO0" pad="CN10_23"/>
<connect gate="G$6" pin="D31/QSPI_BK1_IO2" pad="CN10_25"/>
<connect gate="G$6" pin="D32/TIMER_C_PWM1" pad="CN10_29"/>
<connect gate="G$6" pin="D33/TIMER_D_PWM1" pad="CN10_31"/>
<connect gate="G$6" pin="D34/TIMER_B_ETR" pad="CN10_33"/>
<connect gate="G$6" pin="D35/TIMER_C_PWM3" pad="CN10_34"/>
<connect gate="G$6" pin="D36/TIMER_C_PWM2" pad="CN10_32"/>
<connect gate="G$6" pin="D37/TIMER_A_BKIN1" pad="CN10_30"/>
<connect gate="G$6" pin="D38/IO" pad="CN10_28"/>
<connect gate="G$6" pin="D39/TIMER_A_PWM3N" pad="CN10_26"/>
<connect gate="G$6" pin="D4/IO" pad="CN10_8"/>
<connect gate="G$6" pin="D40/TIMER_A_PWM2N" pad="CN10_24"/>
<connect gate="G$6" pin="D41/TIMER_A_ETR" pad="CN10_20"/>
<connect gate="G$6" pin="D42/TIMER_A_PWM1N" pad="CN10_18"/>
<connect gate="G$6" pin="D5/TIMER_A_PWM2" pad="CN10_6"/>
<connect gate="G$6" pin="D6/TIMER_A_PWM1" pad="CN10_4"/>
<connect gate="G$6" pin="D7/IO" pad="CN10_2"/>
<connect gate="G$6" pin="GND_CN10" pad="CN10_5 CN10_17 CN10_22 CN10_27"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" STM32F746ZG, mbed-Enabled Development Nucleo-144 STM32F7 ARM® Cortex®-M7 MCU 32-Bit Embedded Evaluation Board "/>
<attribute name="MF" value="STMicroelectronics"/>
<attribute name="MP" value="NUCLEO-F746ZG"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="USB3076-XX-X_REVC">
<packages>
<package name="GCT_USB3076-XX-X_REVC">
<circle x="-1.2954" y="3.785" radius="0.1016" width="0.2" layer="21"/>
<wire x1="-6" y1="-1.45" x2="6" y2="-1.45" width="0.2" layer="51"/>
<wire x1="-3.7" y1="-2.8" x2="3.7" y2="-2.8" width="0.1" layer="51"/>
<wire x1="-3.7" y1="2.75" x2="3.7" y2="2.75" width="0.1" layer="51"/>
<wire x1="3.7" y1="-2.8" x2="3.7" y2="2.75" width="0.1" layer="51"/>
<wire x1="-3.7" y1="-2.8" x2="-3.7" y2="2.75" width="0.1" layer="51"/>
<wire x1="-4.5" y1="-3.025" x2="4.5" y2="-3.025" width="0.05" layer="39"/>
<wire x1="0" y1="-0.508" x2="0" y2="0.508" width="0.1" layer="39"/>
<wire x1="-0.508" y1="0" x2="0.508" y2="0" width="0.1" layer="39"/>
<wire x1="-4.5" y1="3.725" x2="4.5" y2="3.725" width="0.05" layer="39"/>
<wire x1="4.5" y1="-3.025" x2="4.5" y2="3.725" width="0.05" layer="39"/>
<wire x1="-4.5" y1="-3.025" x2="-4.5" y2="3.725" width="0.05" layer="39"/>
<wire x1="-3.7" y1="2.75" x2="-3.2" y2="2.75" width="0.2" layer="21"/>
<wire x1="-3.7" y1="1.305" x2="-3.7" y2="2.75" width="0.2" layer="21"/>
<wire x1="3.7" y1="1.295" x2="3.7" y2="2.75" width="0.2" layer="21"/>
<wire x1="3.2" y1="2.75" x2="3.7" y2="2.75" width="0.2" layer="21"/>
<text x="-1.90838125" y="-2.56955" size="0.667859375" layer="51" ratio="15" rot="SR0">PCB Edge</text>
<text x="-3.810590625" y="4.420690625" size="2.03231875" layer="25" ratio="13" rot="SR0">&gt;NAME</text>
<text x="-3.811709375" y="-5.74256875" size="2.032909375" layer="27" ratio="13" rot="SR0">&gt;VALUE</text>
<polygon width="0.001" layer="31">
<vertex x="-3.799" y="0"/>
<vertex x="-3.799" y="0.4" curve="-90"/>
<vertex x="-3.574" y="0.625" curve="-90"/>
<vertex x="-3.349" y="0.4"/>
<vertex x="-3.349" y="0"/>
<vertex x="-3.049" y="0"/>
<vertex x="-3.049" y="0.355" curve="90"/>
<vertex x="-3.574" y="0.925" curve="90"/>
<vertex x="-4.099" y="0.4"/>
<vertex x="-4.099" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="-3.349" y="0"/>
<vertex x="-3.349" y="-0.4" curve="-90"/>
<vertex x="-3.574" y="-0.625" curve="-90"/>
<vertex x="-3.799" y="-0.4"/>
<vertex x="-3.799" y="0"/>
<vertex x="-4.099" y="0"/>
<vertex x="-4.099" y="-0.355" curve="90"/>
<vertex x="-3.574" y="-0.925" curve="90"/>
<vertex x="-3.049" y="-0.4"/>
<vertex x="-3.049" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="-3.799" y="0"/>
<vertex x="-3.799" y="0.4" curve="-90"/>
<vertex x="-3.574" y="0.625" curve="-90"/>
<vertex x="-3.349" y="0.4"/>
<vertex x="-3.349" y="0"/>
<vertex x="-3.049" y="0"/>
<vertex x="-3.049" y="0.355" curve="90"/>
<vertex x="-3.574" y="0.925" curve="90"/>
<vertex x="-4.099" y="0.4"/>
<vertex x="-4.099" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="-3.349" y="0"/>
<vertex x="-3.349" y="-0.4" curve="-90"/>
<vertex x="-3.574" y="-0.625" curve="-90"/>
<vertex x="-3.799" y="-0.4"/>
<vertex x="-3.799" y="0"/>
<vertex x="-4.099" y="0"/>
<vertex x="-4.099" y="-0.355" curve="90"/>
<vertex x="-3.574" y="-0.925" curve="90"/>
<vertex x="-3.049" y="-0.4"/>
<vertex x="-3.049" y="0"/>
</polygon>
<rectangle x1="-4.30366875" y1="-1.15125" x2="-2.849" y2="1.15" layer="29"/>
<wire x1="-3.8" y1="0.401" x2="-3.575" y2="0.626" width="0" layer="46" curve="-90"/>
<wire x1="-3.575" y1="0.626" x2="-3.35" y2="0.402" width="0" layer="46" curve="-90"/>
<wire x1="-3.35" y1="0.402" x2="-3.35" y2="-0.4" width="0" layer="46"/>
<wire x1="-3.8" y1="-0.4" x2="-3.8" y2="0.401" width="0" layer="46"/>
<polygon width="0.001" layer="1">
<vertex x="-3.8" y="0"/>
<vertex x="-3.8" y="0.4" curve="-90"/>
<vertex x="-3.575" y="0.625" curve="-90"/>
<vertex x="-3.35" y="0.4"/>
<vertex x="-3.35" y="0"/>
<vertex x="-3.05" y="0"/>
<vertex x="-3.05" y="0.35" curve="90"/>
<vertex x="-3.575" y="0.925" curve="90"/>
<vertex x="-4.1" y="0.4"/>
<vertex x="-4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="1">
<vertex x="-3.35" y="0"/>
<vertex x="-3.35" y="-0.4" curve="-90"/>
<vertex x="-3.575" y="-0.625" curve="-90"/>
<vertex x="-3.8" y="-0.4"/>
<vertex x="-3.8" y="0"/>
<vertex x="-4.1" y="0"/>
<vertex x="-4.1" y="-0.35" curve="90"/>
<vertex x="-3.575" y="-0.925" curve="90"/>
<vertex x="-3.05" y="-0.4"/>
<vertex x="-3.05" y="0"/>
</polygon>
<wire x1="-3.8" y1="-0.4" x2="-3.575" y2="-0.625" width="0" layer="46" curve="90"/>
<wire x1="-3.575" y1="-0.625" x2="-3.35" y2="-0.4" width="0" layer="46" curve="90"/>
<polygon width="0.001" layer="16">
<vertex x="-3.8" y="0"/>
<vertex x="-3.8" y="0.4" curve="-90"/>
<vertex x="-3.575" y="0.625" curve="-90"/>
<vertex x="-3.35" y="0.4"/>
<vertex x="-3.35" y="0"/>
<vertex x="-3.05" y="0"/>
<vertex x="-3.05" y="0.35" curve="90"/>
<vertex x="-3.575" y="0.925" curve="90"/>
<vertex x="-4.1" y="0.4"/>
<vertex x="-4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="16">
<vertex x="-3.35" y="0"/>
<vertex x="-3.35" y="-0.4" curve="-90"/>
<vertex x="-3.575" y="-0.625" curve="-90"/>
<vertex x="-3.8" y="-0.4"/>
<vertex x="-3.8" y="0"/>
<vertex x="-4.1" y="0"/>
<vertex x="-4.1" y="-0.35" curve="90"/>
<vertex x="-3.575" y="-0.925" curve="90"/>
<vertex x="-3.05" y="-0.4"/>
<vertex x="-3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="-3.8" y="0"/>
<vertex x="-3.8" y="0.4" curve="-90"/>
<vertex x="-3.575" y="0.625" curve="-90"/>
<vertex x="-3.35" y="0.4"/>
<vertex x="-3.35" y="0"/>
<vertex x="-3.05" y="0"/>
<vertex x="-3.05" y="0.35" curve="90"/>
<vertex x="-3.575" y="0.925" curve="90"/>
<vertex x="-4.1" y="0.4"/>
<vertex x="-4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="-3.35" y="0"/>
<vertex x="-3.35" y="-0.4" curve="-90"/>
<vertex x="-3.575" y="-0.625" curve="-90"/>
<vertex x="-3.8" y="-0.4"/>
<vertex x="-3.8" y="0"/>
<vertex x="-4.1" y="0"/>
<vertex x="-4.1" y="-0.35" curve="90"/>
<vertex x="-3.575" y="-0.925" curve="90"/>
<vertex x="-3.05" y="-0.4"/>
<vertex x="-3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="-3.8" y="0"/>
<vertex x="-3.8" y="0.4" curve="-90"/>
<vertex x="-3.575" y="0.625" curve="-90"/>
<vertex x="-3.35" y="0.4"/>
<vertex x="-3.35" y="0"/>
<vertex x="-3.05" y="0"/>
<vertex x="-3.05" y="0.35" curve="90"/>
<vertex x="-3.575" y="0.925" curve="90"/>
<vertex x="-4.1" y="0.4"/>
<vertex x="-4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="-3.35" y="0"/>
<vertex x="-3.35" y="-0.4" curve="-90"/>
<vertex x="-3.575" y="-0.625" curve="-90"/>
<vertex x="-3.8" y="-0.4"/>
<vertex x="-3.8" y="0"/>
<vertex x="-4.1" y="0"/>
<vertex x="-4.1" y="-0.35" curve="90"/>
<vertex x="-3.575" y="-0.925" curve="90"/>
<vertex x="-3.05" y="-0.4"/>
<vertex x="-3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="3.351" y="0"/>
<vertex x="3.351" y="0.4" curve="-90"/>
<vertex x="3.576" y="0.625" curve="-90"/>
<vertex x="3.801" y="0.4"/>
<vertex x="3.801" y="0"/>
<vertex x="4.101" y="0"/>
<vertex x="4.101" y="0.355" curve="90"/>
<vertex x="3.576" y="0.925" curve="90"/>
<vertex x="3.051" y="0.4"/>
<vertex x="3.051" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="3.801" y="0"/>
<vertex x="3.801" y="-0.4" curve="-90"/>
<vertex x="3.576" y="-0.625" curve="-90"/>
<vertex x="3.351" y="-0.4"/>
<vertex x="3.351" y="0"/>
<vertex x="3.051" y="0"/>
<vertex x="3.051" y="-0.355" curve="90"/>
<vertex x="3.576" y="-0.925" curve="90"/>
<vertex x="4.101" y="-0.4"/>
<vertex x="4.101" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="3.351" y="0"/>
<vertex x="3.351" y="0.4" curve="-90"/>
<vertex x="3.576" y="0.625" curve="-90"/>
<vertex x="3.801" y="0.4"/>
<vertex x="3.801" y="0"/>
<vertex x="4.101" y="0"/>
<vertex x="4.101" y="0.355" curve="90"/>
<vertex x="3.576" y="0.925" curve="90"/>
<vertex x="3.051" y="0.4"/>
<vertex x="3.051" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="3.801" y="0"/>
<vertex x="3.801" y="-0.4" curve="-90"/>
<vertex x="3.576" y="-0.625" curve="-90"/>
<vertex x="3.351" y="-0.4"/>
<vertex x="3.351" y="0"/>
<vertex x="3.051" y="0"/>
<vertex x="3.051" y="-0.355" curve="90"/>
<vertex x="3.576" y="-0.925" curve="90"/>
<vertex x="4.101" y="-0.4"/>
<vertex x="4.101" y="0"/>
</polygon>
<rectangle x1="2.85585" y1="-1.151959375" x2="4.301" y2="1.15" layer="29"/>
<wire x1="3.35" y1="0.401" x2="3.575" y2="0.626" width="0" layer="46" curve="-90"/>
<wire x1="3.575" y1="0.626" x2="3.8" y2="0.402" width="0" layer="46" curve="-90"/>
<wire x1="3.8" y1="0.402" x2="3.8" y2="-0.4" width="0" layer="46"/>
<wire x1="3.35" y1="-0.4" x2="3.35" y2="0.401" width="0" layer="46"/>
<polygon width="0.001" layer="1">
<vertex x="3.35" y="0"/>
<vertex x="3.35" y="0.4" curve="-90"/>
<vertex x="3.575" y="0.625" curve="-90"/>
<vertex x="3.8" y="0.4"/>
<vertex x="3.8" y="0"/>
<vertex x="4.1" y="0"/>
<vertex x="4.1" y="0.35" curve="90"/>
<vertex x="3.575" y="0.925" curve="90"/>
<vertex x="3.05" y="0.4"/>
<vertex x="3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="1">
<vertex x="3.8" y="0"/>
<vertex x="3.8" y="-0.4" curve="-90"/>
<vertex x="3.575" y="-0.625" curve="-90"/>
<vertex x="3.35" y="-0.4"/>
<vertex x="3.35" y="0"/>
<vertex x="3.05" y="0"/>
<vertex x="3.05" y="-0.35" curve="90"/>
<vertex x="3.575" y="-0.925" curve="90"/>
<vertex x="4.1" y="-0.4"/>
<vertex x="4.1" y="0"/>
</polygon>
<wire x1="3.35" y1="-0.4" x2="3.575" y2="-0.625" width="0" layer="46" curve="90"/>
<wire x1="3.575" y1="-0.625" x2="3.8" y2="-0.4" width="0" layer="46" curve="90"/>
<polygon width="0.001" layer="16">
<vertex x="3.35" y="0"/>
<vertex x="3.35" y="0.4" curve="-90"/>
<vertex x="3.575" y="0.625" curve="-90"/>
<vertex x="3.8" y="0.4"/>
<vertex x="3.8" y="0"/>
<vertex x="4.1" y="0"/>
<vertex x="4.1" y="0.35" curve="90"/>
<vertex x="3.575" y="0.925" curve="90"/>
<vertex x="3.05" y="0.4"/>
<vertex x="3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="16">
<vertex x="3.8" y="0"/>
<vertex x="3.8" y="-0.4" curve="-90"/>
<vertex x="3.575" y="-0.625" curve="-90"/>
<vertex x="3.35" y="-0.4"/>
<vertex x="3.35" y="0"/>
<vertex x="3.05" y="0"/>
<vertex x="3.05" y="-0.35" curve="90"/>
<vertex x="3.575" y="-0.925" curve="90"/>
<vertex x="4.1" y="-0.4"/>
<vertex x="4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="3.35" y="0"/>
<vertex x="3.35" y="0.4" curve="-90"/>
<vertex x="3.575" y="0.625" curve="-90"/>
<vertex x="3.8" y="0.4"/>
<vertex x="3.8" y="0"/>
<vertex x="4.1" y="0"/>
<vertex x="4.1" y="0.35" curve="90"/>
<vertex x="3.575" y="0.925" curve="90"/>
<vertex x="3.05" y="0.4"/>
<vertex x="3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="31">
<vertex x="3.8" y="0"/>
<vertex x="3.8" y="-0.4" curve="-90"/>
<vertex x="3.575" y="-0.625" curve="-90"/>
<vertex x="3.35" y="-0.4"/>
<vertex x="3.35" y="0"/>
<vertex x="3.05" y="0"/>
<vertex x="3.05" y="-0.35" curve="90"/>
<vertex x="3.575" y="-0.925" curve="90"/>
<vertex x="4.1" y="-0.4"/>
<vertex x="4.1" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="3.35" y="0"/>
<vertex x="3.35" y="0.4" curve="-90"/>
<vertex x="3.575" y="0.625" curve="-90"/>
<vertex x="3.8" y="0.4"/>
<vertex x="3.8" y="0"/>
<vertex x="4.1" y="0"/>
<vertex x="4.1" y="0.35" curve="90"/>
<vertex x="3.575" y="0.925" curve="90"/>
<vertex x="3.05" y="0.4"/>
<vertex x="3.05" y="0"/>
</polygon>
<polygon width="0.001" layer="32">
<vertex x="3.8" y="0"/>
<vertex x="3.8" y="-0.4" curve="-90"/>
<vertex x="3.575" y="-0.625" curve="-90"/>
<vertex x="3.35" y="-0.4"/>
<vertex x="3.35" y="0"/>
<vertex x="3.05" y="0"/>
<vertex x="3.05" y="-0.35" curve="90"/>
<vertex x="3.575" y="-0.925" curve="90"/>
<vertex x="4.1" y="-0.4"/>
<vertex x="4.1" y="0"/>
</polygon>
<rectangle x1="-4.306859375" y1="-1.1521" x2="-2.849" y2="1.15" layer="30"/>
<rectangle x1="2.85383125" y1="-1.151140625" x2="4.301" y2="1.15" layer="30"/>
<smd name="1" x="-1.3" y="2.65" dx="0.4" dy="1.4" layer="1"/>
<smd name="2" x="-0.65" y="2.65" dx="0.4" dy="1.4" layer="1"/>
<smd name="3" x="0" y="2.65" dx="0.4" dy="1.4" layer="1"/>
<smd name="4" x="0.66" y="2.65" dx="0.4" dy="1.4" layer="1"/>
<smd name="5" x="1.3" y="2.65" dx="0.4" dy="1.4" layer="1"/>
<smd name="8" x="-2.32" y="2.23" dx="1.15" dy="1.45" layer="1"/>
<smd name="9" x="2.32" y="2.23" dx="1.15" dy="1.45" layer="1"/>
<smd name="10" x="-1.125" y="0" dx="1.75" dy="1.9" layer="1"/>
<smd name="11" x="1.125" y="0" dx="1.75" dy="1.9" layer="1"/>
<hole x="-3.575" y="0" drill="0.45"/>
<smd name="6" x="-3.549" y="0.73" dx="0.1" dy="0.1" layer="1" stop="no" cream="no"/>
<hole x="3.575" y="0" drill="0.45"/>
<smd name="7" x="3.601" y="0.73" dx="0.1" dy="0.1" layer="1" stop="no" cream="no"/>
</package>
</packages>
<symbols>
<symbol name="USB3076-XX-X_REVC">
<wire x1="-5.08" y1="10.16" x2="5.08" y2="10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="-10.16" x2="-5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-10.16" x2="-5.08" y2="10.16" width="0.254" layer="94"/>
<text x="-5.082759375" y="10.6738" size="1.77896875" layer="95">&gt;NAME</text>
<text x="-5.08225" y="-12.7056" size="1.778790625" layer="96">&gt;VALUE</text>
<pin name="VBUS" x="-10.16" y="7.62" visible="pin" length="middle" direction="pwr"/>
<pin name="D-" x="-10.16" y="5.08" visible="pin" length="middle"/>
<pin name="D+" x="-10.16" y="2.54" visible="pin" length="middle"/>
<pin name="GND" x="-10.16" y="-2.54" visible="pin" length="middle" direction="pwr"/>
<pin name="SHIELD" x="-10.16" y="-7.62" visible="pin" length="middle" direction="pwr"/>
<pin name="ID" x="-10.16" y="0" visible="pin" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="USB3076-XX-X_REVC" prefix="J">
<description>Micro USB Receptacle, Type B, SMT, Horizontal, Bottom Mount w/out Peg, w/out Shell Stakes, w/out Mating Face Lead-In &lt;a href="https://pricing.snapeda.com/parts/USB3076-30-A/Global%20Connector%20Technology/view-part?ref=eda"&gt;Check prices&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="USB3076-XX-X_REVC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="GCT_USB3076-XX-X_REVC">
<connects>
<connect gate="G$1" pin="D+" pad="3"/>
<connect gate="G$1" pin="D-" pad="2"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="ID" pad="4"/>
<connect gate="G$1" pin="SHIELD" pad="6 7 8 9 10 11"/>
<connect gate="G$1" pin="VBUS" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="DESCRIPTION" value=" USB - micro B USB 2.0 Receptacle Connector 5 Position Surface Mount, Right Angle; Through Hole, 2.35mm profile, 5 Pins, Horizontal, Bottom mount "/>
<attribute name="MF" value="Global Connector Technology"/>
<attribute name="MP" value="USB3076-30-A"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
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
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
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
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="FRAME_A_L">
<frame x1="0" y1="0" x2="279.4" y2="215.9" columns="6" rows="5" layer="94" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A_L" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt; A Size , 8 1/2 x 11 INCH, Landscape&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="FRAME_A_L" x="0" y="0" addlevel="always"/>
<gate name="G$2" symbol="DOCFIELD" x="172.72" y="0" addlevel="always"/>
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
<library name="640455-5">
<packages>
<package name="TE_640455-5">
<wire x1="-11.43" y1="-8.195" x2="-11.43" y2="-0.445" width="0.127" layer="51"/>
<wire x1="-11.43" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="51"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="1.27" y1="-8.195" x2="-11.43" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-11.43" y1="-8.195" x2="-11.43" y2="-10.475" width="0.127" layer="51"/>
<wire x1="-11.43" y1="-10.475" x2="1.27" y2="-10.475" width="0.127" layer="51"/>
<wire x1="1.27" y1="-10.475" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-11.43" y1="-8.195" x2="-11.43" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-11.43" y1="-0.445" x2="-11.165" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.005" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="21"/>
<wire x1="-11.43" y1="-8.195" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-11.68" y1="-10.725" x2="-11.68" y2="0.935" width="0.05" layer="39"/>
<wire x1="-11.68" y1="0.935" x2="1.52" y2="0.935" width="0.05" layer="39"/>
<wire x1="1.52" y1="0.935" x2="1.52" y2="-10.725" width="0.05" layer="39"/>
<wire x1="1.52" y1="-10.725" x2="-11.68" y2="-10.725" width="0.05" layer="39"/>
<text x="-12.43" y="1.935" size="1.27" layer="25">&gt;NAME</text>
<text x="-12.43" y="-12.725" size="1.27" layer="27">&gt;VALUE</text>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="21"/>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="51"/>
<pad name="1" x="0" y="0" drill="1.02" diameter="1.37" shape="square"/>
<pad name="2" x="-2.54" y="0" drill="1.02" diameter="1.37"/>
<pad name="3" x="-5.08" y="0" drill="1.02" diameter="1.37"/>
<pad name="4" x="-7.62" y="0" drill="1.02" diameter="1.37"/>
<pad name="5" x="-10.16" y="0" drill="1.02" diameter="1.37"/>
</package>
</packages>
<symbols>
<symbol name="640455-5">
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<text x="-5.58" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-10.16" y="5.08" length="middle" direction="pas"/>
<pin name="2" x="-10.16" y="2.54" length="middle" direction="pas"/>
<pin name="3" x="-10.16" y="0" length="middle" direction="pas"/>
<pin name="4" x="-10.16" y="-2.54" length="middle" direction="pas"/>
<pin name="5" x="-10.16" y="-5.08" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="640455-5" prefix="J">
<gates>
<gate name="G$1" symbol="640455-5" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TE_640455-5">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="COMMENT" value="640455-5"/>
<attribute name="DESCRIPTION" value=" MTA-100 5 Position Through Hole Single Row Right Angle Wire to Board Header "/>
<attribute name="DIGI-KEY_PART_NUMBER" value="A19453-ND"/>
<attribute name="DIGI-KEY_PURCHASE_URL" value="https://www.digikey.de/product-detail/en/te-connectivity-amp-connectors/640455-5/A19453-ND/259000?utm_source=snapeda&amp;utm_medium=aggregator&amp;utm_campaign=symbol"/>
<attribute name="MF" value="TE Connectivity"/>
<attribute name="MP" value="640455-5"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="TE_PURCHASE_URL" value="https://www.te.com/usa-en/product-640455-5.html?te_bu=Cor&amp;te_type=disp&amp;te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&amp;elqCampaignId=32493"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="640455-2">
<packages>
<package name="TE_640455-2">
<wire x1="-3.81" y1="-8.195" x2="-3.81" y2="-0.445" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="51"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="1.27" y1="-8.195" x2="-3.81" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-8.195" x2="-3.81" y2="-10.475" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-10.475" x2="1.27" y2="-10.475" width="0.127" layer="51"/>
<wire x1="1.27" y1="-10.475" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-3.81" y1="-8.195" x2="-3.81" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-0.445" x2="-3.545" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.005" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="21"/>
<wire x1="-3.81" y1="-8.195" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-4.06" y1="-10.725" x2="-4.06" y2="0.935" width="0.05" layer="39"/>
<wire x1="-4.06" y1="0.935" x2="1.52" y2="0.935" width="0.05" layer="39"/>
<wire x1="1.52" y1="0.935" x2="1.52" y2="-10.725" width="0.05" layer="39"/>
<wire x1="1.52" y1="-10.725" x2="-4.06" y2="-10.725" width="0.05" layer="39"/>
<text x="-4.81" y="1.935" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.81" y="-12.725" size="1.27" layer="27">&gt;VALUE</text>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="21"/>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="51"/>
<pad name="1" x="0" y="0" drill="1.02" diameter="1.37" shape="square"/>
<pad name="2" x="-2.54" y="0" drill="1.02" diameter="1.37"/>
</package>
</packages>
<symbols>
<symbol name="640455-2">
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<text x="-5.58" y="5.08" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-10.16" y="2.54" length="middle" direction="pas"/>
<pin name="2" x="-10.16" y="0" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="640455-2" prefix="J">
<description> &lt;a href="https://pricing.snapeda.com/parts/640455-2/TE%20Connectivity/view-part?ref=eda"&gt;Check prices&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="640455-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TE_640455-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="COMMENT" value="640455-2"/>
<attribute name="DESCRIPTION" value=" MTA-100 2 Position 2.54 mm Single Row Right Angle Wire to Board Header "/>
<attribute name="EU_ROHS_COMPLIANCE" value="Compliant"/>
<attribute name="MF" value="TE Connectivity"/>
<attribute name="MP" value="640455-2"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
<attribute name="PURCHASE-URL" value="https://pricing.snapeda.com/search/part/640455-2/?ref=eda"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="640455-4">
<packages>
<package name="TE_640455-4">
<wire x1="-8.89" y1="-8.195" x2="-8.89" y2="-0.445" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="51"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="1.27" y1="-8.195" x2="-8.89" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-8.195" x2="-8.89" y2="-10.475" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-10.475" x2="1.27" y2="-10.475" width="0.127" layer="51"/>
<wire x1="1.27" y1="-10.475" x2="1.27" y2="-8.195" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-8.195" x2="-8.89" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.27" y1="-0.445" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-0.445" x2="-8.625" y2="-0.445" width="0.127" layer="21"/>
<wire x1="1.005" y1="-0.445" x2="1.27" y2="-0.445" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-8.195" x2="1.27" y2="-8.195" width="0.127" layer="21"/>
<wire x1="-9.14" y1="-10.725" x2="-9.14" y2="0.935" width="0.05" layer="39"/>
<wire x1="-9.14" y1="0.935" x2="1.52" y2="0.935" width="0.05" layer="39"/>
<wire x1="1.52" y1="0.935" x2="1.52" y2="-10.725" width="0.05" layer="39"/>
<wire x1="1.52" y1="-10.725" x2="-9.14" y2="-10.725" width="0.05" layer="39"/>
<text x="-9.89" y="1.935" size="1.27" layer="25">&gt;NAME</text>
<text x="-9.89" y="-12.725" size="1.27" layer="27">&gt;VALUE</text>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="21"/>
<circle x="1.92" y="0" radius="0.1" width="0.2" layer="51"/>
<pad name="1" x="0" y="0" drill="1.02" diameter="1.37" shape="square"/>
<pad name="2" x="-2.54" y="0" drill="1.02" diameter="1.37"/>
<pad name="3" x="-5.08" y="0" drill="1.02" diameter="1.37"/>
<pad name="4" x="-7.62" y="0" drill="1.02" diameter="1.37"/>
</package>
</packages>
<symbols>
<symbol name="640455-4">
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="-5.58" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-10.16" y="5.08" length="middle" direction="pas"/>
<pin name="2" x="-10.16" y="2.54" length="middle" direction="pas"/>
<pin name="3" x="-10.16" y="0" length="middle" direction="pas"/>
<pin name="4" x="-10.16" y="-2.54" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="640455-4" prefix="J">
<description> &lt;a href="https://pricing.snapeda.com/parts/640455-4/TE%20Connectivity/view-part?ref=eda"&gt;Check prices&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="640455-4" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TE_640455-4">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="COMMENT" value="640455-4"/>
<attribute name="DESCRIPTION" value=" Headers &amp; Receptacles cable a placa 8 POS MONO SHAPE MKII TAB ASS'Y GW 750.N TYCO / TE CONNECTIVITY "/>
<attribute name="EU_ROHS_COMPLIANCE" value="Compliant"/>
<attribute name="MF" value="TE Connectivity"/>
<attribute name="MP" value="640455-4"/>
<attribute name="PACKAGE" value="None"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SJ-3523-SMT-TR">
<packages>
<package name="CUI_SJ-3523-SMT-TR">
<wire x1="-3.5" y1="-3" x2="-3.5" y2="-2.5" width="0.127" layer="21"/>
<wire x1="-3.5" y1="-2.5" x2="-3.5" y2="2.5" width="0.127" layer="21"/>
<wire x1="-3.5" y1="2.5" x2="-3.5" y2="3" width="0.127" layer="21"/>
<wire x1="-3.5" y1="-3" x2="-3.5" y2="3" width="0.127" layer="51"/>
<wire x1="-3.5" y1="3" x2="11" y2="3" width="0.127" layer="51"/>
<wire x1="11" y1="3" x2="11" y2="-3" width="0.127" layer="51"/>
<wire x1="11" y1="-3" x2="-3.5" y2="-3" width="0.127" layer="51"/>
<wire x1="-3.5" y1="3" x2="-0.4" y2="3" width="0.127" layer="21"/>
<wire x1="2.2" y1="3" x2="11" y2="3" width="0.127" layer="21"/>
<wire x1="11" y1="3" x2="11" y2="-3" width="0.127" layer="21"/>
<wire x1="-3.5" y1="-3" x2="-2.4" y2="-3" width="0.127" layer="21"/>
<wire x1="0.2" y1="-3" x2="6.7" y2="-3" width="0.127" layer="21"/>
<wire x1="-3.75" y1="5.35" x2="11.25" y2="5.35" width="0.05" layer="39"/>
<wire x1="11.25" y1="5.35" x2="11.25" y2="-5.35" width="0.05" layer="39"/>
<wire x1="11.25" y1="-5.35" x2="-3.75" y2="-5.35" width="0.05" layer="39"/>
<text x="-3.105690625" y="5.309740625" size="1.27233125" layer="25">&gt;NAME</text>
<text x="-3.20573125" y="-6.61181875" size="1.27228125" layer="27">&gt;VALUE</text>
<circle x="-4.3" y="-3.3" radius="0.1" width="0.2" layer="21"/>
<circle x="-4.3" y="-3.3" radius="0.1" width="0.2" layer="51"/>
<wire x1="9.9" y1="-3" x2="11" y2="-3" width="0.127" layer="21"/>
<wire x1="-3.5" y1="2.5" x2="-6" y2="2.5" width="0.127" layer="21"/>
<wire x1="-6" y1="2.5" x2="-6" y2="-2.5" width="0.127" layer="21"/>
<wire x1="-6" y1="-2.5" x2="-3.5" y2="-2.5" width="0.127" layer="21"/>
<wire x1="-3.5" y1="2.5" x2="-6" y2="2.5" width="0.127" layer="51"/>
<wire x1="-6" y1="2.5" x2="-6" y2="-2.5" width="0.127" layer="51"/>
<wire x1="-6" y1="-2.5" x2="-3.5" y2="-2.5" width="0.127" layer="51"/>
<wire x1="-3.75" y1="5.35" x2="-3.75" y2="2.75" width="0.05" layer="39"/>
<wire x1="-3.75" y1="2.75" x2="-6.25" y2="2.75" width="0.05" layer="39"/>
<wire x1="-6.25" y1="2.75" x2="-6.25" y2="-2.75" width="0.05" layer="39"/>
<wire x1="-6.25" y1="-2.75" x2="-3.75" y2="-2.75" width="0.05" layer="39"/>
<wire x1="-3.75" y1="-2.75" x2="-3.75" y2="-5.35" width="0.05" layer="39"/>
<hole x="0" y="0" drill="1.7"/>
<smd name="3" x="0.9" y="3.7" dx="2.2" dy="2.8" layer="1"/>
<smd name="1" x="-1.1" y="-3.7" dx="2.2" dy="2.8" layer="1"/>
<smd name="2" x="8.3" y="-3.7" dx="2.8" dy="2.8" layer="1"/>
<hole x="7" y="0" drill="1.7"/>
</package>
</packages>
<symbols>
<symbol name="SJ-3523-SMT-TR">
<wire x1="-3.429" y1="1.27" x2="-3.429" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-3.429" y1="-2.54" x2="-2.159" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="-2.54" x2="-2.159" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.27" x2="-2.794" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-2.794" y1="1.27" x2="-3.429" y2="1.27" width="0.1524" layer="94"/>
<wire x1="-2.794" y1="1.27" x2="-2.794" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-2.794" y1="2.54" x2="5.08" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.27" y1="0" x2="0.254" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="0.254" y1="-1.27" x2="-0.762" y2="0" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-5.100409375" y="5.737959375" size="2.201440625" layer="95">&gt;NAME</text>
<text x="-5.10061875" y="-7.65093125" size="2.20203125" layer="96">&gt;VALUE</text>
<wire x1="5.08" y1="0" x2="1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-2.54" x2="3.556" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="1.524" y1="-2.54" x2="2.54" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.27" x2="3.556" y2="-2.54" width="0.1524" layer="94"/>
<pin name="1" x="7.62" y="2.54" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="3" x="7.62" y="0" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="2" x="7.62" y="-2.54" visible="pad" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SJ-3523-SMT-TR" prefix="J">
<description>&lt;b&gt;Audio Jack Connector&lt;/b&gt; 3.5 mm Low Profile Surface Mount Stereo Jack, 3 Pin Right-Angle &lt;a href="https://pricing.snapeda.com/parts/SJ-3523-SMT-TR/CUI%20Devices/view-part?ref=eda"&gt;Check prices&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="SJ-3523-SMT-TR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CUI_SJ-3523-SMT-TR">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="AVAILABILITY" value="In Stock"/>
<attribute name="CUI_PURCHASE_URL" value="https://www.cuidevices.com/product/interconnect/connectors/audio-connectors/jacks/sj-352x-smt-series?utm_source=snapeda.com&amp;utm_medium=referral&amp;utm_campaign=snapedaBOM"/>
<attribute name="DESCRIPTION" value="3.5 mm, Stereo, Right Angle, Surface Mount (SMT), 3 Conductors, 0~1 Internal Switches, Audio Jack Connector"/>
<attribute name="MF" value="CUI Devices"/>
<attribute name="MP" value="SJ-3523-SMT-TR"/>
<attribute name="PACKAGE" value="LGA-10 STMicroelectronics"/>
<attribute name="PRICE" value="None"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SamacSys_Parts">
<description>&lt;b&gt;https://componentsearchengine.com&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="RHDR6W76P0X254_1X6_1524X254X82">
<description>&lt;b&gt;929850-01-06-RB&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1.25" diameter="1.875" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.25" diameter="1.875"/>
<pad name="3" x="5.08" y="0" drill="1.25" diameter="1.875"/>
<pad name="4" x="7.62" y="0" drill="1.25" diameter="1.875"/>
<pad name="5" x="10.16" y="0" drill="1.25" diameter="1.875"/>
<pad name="6" x="12.7" y="0" drill="1.25" diameter="1.875"/>
<text x="0" y="0" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.52" y1="-1.52" x2="-1.52" y2="1.555" width="0.05" layer="51"/>
<wire x1="-1.52" y1="1.555" x2="14.255" y2="1.555" width="0.05" layer="51"/>
<wire x1="14.255" y1="1.555" x2="14.255" y2="-1.52" width="0.05" layer="51"/>
<wire x1="14.255" y1="-1.52" x2="-1.52" y2="-1.52" width="0.05" layer="51"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.1" layer="51"/>
<wire x1="-1.27" y1="1.27" x2="13.97" y2="1.27" width="0.1" layer="51"/>
<wire x1="13.97" y1="1.27" x2="13.97" y2="-1.27" width="0.1" layer="51"/>
<wire x1="13.97" y1="-1.27" x2="-1.27" y2="-1.27" width="0.1" layer="51"/>
<wire x1="0" y1="-1.27" x2="14.005" y2="-1.27" width="0.2" layer="21"/>
<wire x1="14.005" y1="-1.27" x2="14.005" y2="1.305" width="0.2" layer="21"/>
<wire x1="14.005" y1="1.305" x2="-1.27" y2="1.305" width="0.2" layer="21"/>
<wire x1="-1.27" y1="1.305" x2="-1.27" y2="0" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="929850-01-06-RB">
<wire x1="5.08" y1="2.54" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-15.24" x2="15.24" y2="2.54" width="0.254" layer="94"/>
<wire x1="15.24" y1="-15.24" x2="5.08" y2="-15.24" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-15.24" width="0.254" layer="94"/>
<text x="3.81" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="3.81" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" length="middle"/>
<pin name="2" x="0" y="-2.54" length="middle"/>
<pin name="3" x="0" y="-5.08" length="middle"/>
<pin name="4" x="0" y="-7.62" length="middle"/>
<pin name="5" x="0" y="-10.16" length="middle"/>
<pin name="6" x="0" y="-12.7" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="929850-01-06-RB" prefix="J">
<description>&lt;b&gt;Headers &amp; Wire Housings 6P STRT BRD MNT SKT 1 ROW 30MICRO" AU&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.mouser.fr/datasheet/2/1/ts0815-31700.pdf"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="929850-01-06-RB" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RHDR6W76P0X254_1X6_1524X254X82">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="Headers &amp; Wire Housings 6P STRT BRD MNT SKT 1 ROW 30MICRO&quot; AU" constant="no"/>
<attribute name="HEIGHT" value="8.26mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="3M" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="929850-01-06-RB" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="517-929850-01-06-RB" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/3M-Electronic-Solutions-Division/929850-01-06-RB?qs=s3by4FhMkp1OostaNDHGSw%3D%3D" constant="no"/>
</technology>
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
<part name="A1" library="NUCLEO-F746ZG" deviceset="NUCLEO-F746ZG" device=""/>
<part name="J1" library="USB3076-XX-X_REVC" deviceset="USB3076-XX-X_REVC" device=""/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
<part name="FRAME2" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="FRAME3" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="FRAME4" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY4" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY6" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY7" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY8" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY9" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY10" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY11" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY12" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY13" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY14" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY15" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY24" library="supply2" deviceset="GND" device=""/>
<part name="J2" library="640455-5" deviceset="640455-5" device=""/>
<part name="J3" library="640455-2" deviceset="640455-2" device=""/>
<part name="J4" library="640455-4" deviceset="640455-4" device=""/>
<part name="J5" library="640455-4" deviceset="640455-4" device=""/>
<part name="J6" library="SJ-3523-SMT-TR" deviceset="SJ-3523-SMT-TR" device=""/>
<part name="J7" library="640455-2" deviceset="640455-2" device=""/>
<part name="J8" library="SamacSys_Parts" deviceset="929850-01-06-RB" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-5.08" y="88.9" size="10.16" layer="97" align="center">Nucleo-Board &amp; Power-Supply</text>
<wire x1="-50.8" y1="68.58" x2="53.34" y2="68.58" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="68.58" x2="53.34" y2="-66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="-66.04" x2="-50.8" y2="-66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="-50.8" y1="-66.04" x2="-50.8" y2="68.58" width="0.508" layer="97" style="longdash"/>
<wire x1="68.58" y1="68.58" x2="119.38" y2="68.58" width="0.508" layer="97" style="longdash"/>
<wire x1="119.38" y1="68.58" x2="119.38" y2="27.94" width="0.508" layer="97" style="longdash"/>
<wire x1="119.38" y1="27.94" x2="68.58" y2="27.94" width="0.508" layer="97" style="longdash"/>
<wire x1="68.58" y1="27.94" x2="68.58" y2="68.58" width="0.508" layer="97" style="longdash"/>
<text x="91.948" y="64.262" size="5.08" layer="97" rot="R180" align="center">-5V</text>
</plain>
<instances>
<instance part="A1" gate="G$1" x="0" y="-2.54"/>
<instance part="FRAME2" gate="G$1" x="-134.62" y="-111.76"/>
<instance part="FRAME2" gate="G$2" x="38.1" y="-111.76"/>
<instance part="SUPPLY14" gate="GND" x="20.32" y="-60.96"/>
<instance part="SUPPLY24" gate="GND" x="78.74" y="33.02"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="A1" gate="G$1" pin="GND_CN11"/>
<wire x1="17.78" y1="-55.88" x2="20.32" y2="-55.88" width="0.1524" layer="91" style="longdash"/>
<pinref part="SUPPLY14" gate="GND" pin="GND"/>
<wire x1="20.32" y1="-55.88" x2="20.32" y2="-58.42" width="0.1524" layer="91" style="longdash"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<plain>
<text x="-97.282" y="75.692" size="1.27" layer="97" rot="R90">Floating</text>
<wire x1="-111.76" y1="96.52" x2="-60.96" y2="96.52" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="96.52" x2="-60.96" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="55.88" x2="-111.76" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="-111.76" y1="55.88" x2="-111.76" y2="96.52" width="0.508" layer="97" style="longdash"/>
<text x="5.08" y="109.22" size="10.16" layer="97" align="center">Connectors</text>
<text x="-85.852" y="92.202" size="5.08" layer="97" rot="R180" align="center">Powerbank </text>
<wire x1="-111.76" y1="0" x2="-60.96" y2="0" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="0" x2="-60.96" y2="-40.64" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="-40.64" x2="-111.76" y2="-40.64" width="0.508" layer="97" style="longdash"/>
<wire x1="-111.76" y1="-40.64" x2="-111.76" y2="0" width="0.508" layer="97" style="longdash"/>
<text x="-88.392" y="-4.318" size="5.08" layer="97" rot="R180" align="center">Display</text>
<wire x1="-53.34" y1="96.52" x2="-2.54" y2="96.52" width="0.508" layer="97" style="longdash"/>
<wire x1="-2.54" y1="96.52" x2="-2.54" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="-2.54" y1="55.88" x2="-53.34" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="-53.34" y1="55.88" x2="-53.34" y2="96.52" width="0.508" layer="97" style="longdash"/>
<text x="-27.432" y="92.202" size="5.08" layer="97" rot="R180" align="center">EMG / EKG</text>
<wire x1="5.08" y1="96.52" x2="55.88" y2="96.52" width="0.508" layer="97" style="longdash"/>
<wire x1="55.88" y1="96.52" x2="55.88" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="55.88" y1="55.88" x2="5.08" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="5.08" y1="55.88" x2="5.08" y2="96.52" width="0.508" layer="97" style="longdash"/>
<text x="30.988" y="92.202" size="5.08" layer="97" rot="R180" align="center">Keyboard</text>
<wire x1="63.5" y1="96.52" x2="114.3" y2="96.52" width="0.508" layer="97" style="longdash"/>
<wire x1="114.3" y1="96.52" x2="114.3" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="114.3" y1="55.88" x2="63.5" y2="55.88" width="0.508" layer="97" style="longdash"/>
<wire x1="63.5" y1="55.88" x2="63.5" y2="96.52" width="0.508" layer="97" style="longdash"/>
<text x="89.408" y="92.202" size="5.08" layer="97" rot="R180" align="center">EQ-/VU-Meter</text>
<wire x1="-111.76" y1="48.26" x2="-60.96" y2="48.26" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="48.26" x2="-60.96" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="-60.96" y1="7.62" x2="-111.76" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="-111.76" y1="7.62" x2="-111.76" y2="48.26" width="0.508" layer="97" style="longdash"/>
<text x="-85.852" y="43.942" size="5.08" layer="97" rot="R180" align="center">Gyro / ACC</text>
<wire x1="-53.34" y1="48.26" x2="-2.54" y2="48.26" width="0.508" layer="97" style="longdash"/>
<wire x1="-2.54" y1="48.26" x2="-2.54" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="-2.54" y1="7.62" x2="-53.34" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="-53.34" y1="7.62" x2="-53.34" y2="48.26" width="0.508" layer="97" style="longdash"/>
<text x="-27.432" y="43.942" size="5.08" layer="97" rot="R180" align="center">Headphones</text>
<wire x1="5.08" y1="48.26" x2="55.88" y2="48.26" width="0.508" layer="97" style="longdash"/>
<wire x1="55.88" y1="48.26" x2="55.88" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="55.88" y1="7.62" x2="5.08" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="5.08" y1="7.62" x2="5.08" y2="48.26" width="0.508" layer="97" style="longdash"/>
<text x="30.988" y="43.942" size="5.08" layer="97" rot="R180" align="center">Speaker</text>
<wire x1="63.5" y1="48.26" x2="114.3" y2="48.26" width="0.508" layer="97" style="longdash"/>
<wire x1="114.3" y1="48.26" x2="114.3" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="114.3" y1="7.62" x2="63.5" y2="7.62" width="0.508" layer="97" style="longdash"/>
<wire x1="63.5" y1="7.62" x2="63.5" y2="48.26" width="0.508" layer="97" style="longdash"/>
<text x="86.868" y="43.942" size="5.08" layer="97" rot="R180" align="center">SD-Card</text>
<text x="-17.78" y="15.24" size="1.27" layer="97">1 - Sleeve
2 - Tip
3 - Ring</text>
</plain>
<instances>
<instance part="J1" gate="G$1" x="-86.36" y="76.2"/>
<instance part="SUPPLY1" gate="GND" x="-101.6" y="60.96"/>
<instance part="FRAME3" gate="G$1" x="-124.46" y="-91.44"/>
<instance part="FRAME3" gate="G$2" x="48.26" y="-91.44"/>
<instance part="SUPPLY15" gate="GND" x="-101.6" y="-35.56"/>
<instance part="J2" gate="G$1" x="-33.02" y="73.66" rot="R180"/>
<instance part="J3" gate="G$1" x="25.4" y="73.66" rot="R180"/>
<instance part="J4" gate="G$1" x="78.74" y="73.66" rot="R180"/>
<instance part="J5" gate="G$1" x="-93.98" y="27.94" rot="R180"/>
<instance part="J6" gate="G$1" x="-40.64" y="27.94"/>
<instance part="J7" gate="G$1" x="15.24" y="30.48" rot="R180"/>
<instance part="J8" gate="G$1" x="88.9" y="20.32" rot="R180"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="GND"/>
<wire x1="-96.52" y1="73.66" x2="-101.6" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="73.66" x2="-101.6" y2="68.58" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="SHIELD"/>
<wire x1="-101.6" y1="68.58" x2="-96.52" y2="68.58" width="0.1524" layer="91"/>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
<wire x1="-101.6" y1="68.58" x2="-101.6" y2="63.5" width="0.1524" layer="91"/>
<junction x="-101.6" y="68.58"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="4"/>
<wire x1="-22.86" y1="76.2" x2="-20.32" y2="76.2" width="0.1524" layer="91" style="longdash"/>
<label x="-20.32" y="76.2" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J3" gate="G$1" pin="1"/>
<wire x1="35.56" y1="71.12" x2="38.1" y2="71.12" width="0.1524" layer="91" style="longdash"/>
<label x="38.1" y="71.12" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="88.9" y1="71.12" x2="91.44" y2="71.12" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="71.12" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J5" gate="G$1" pin="3"/>
<wire x1="-83.82" y1="27.94" x2="-81.28" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<label x="-81.28" y="27.94" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J6" gate="G$1" pin="1"/>
<wire x1="-33.02" y1="30.48" x2="-27.94" y2="30.48" width="0.1524" layer="91" style="longdash"/>
<label x="-27.94" y="30.48" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J7" gate="G$1" pin="1"/>
<wire x1="25.4" y1="27.94" x2="27.94" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<label x="27.94" y="27.94" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="6"/>
<wire x1="88.9" y1="33.02" x2="91.44" y2="33.02" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="33.02" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="VBUS"/>
<wire x1="-96.52" y1="83.82" x2="-101.6" y2="83.82" width="0.1524" layer="91"/>
<label x="-101.6" y="83.82" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="5"/>
<wire x1="-22.86" y1="78.74" x2="-20.32" y2="78.74" width="0.1524" layer="91" style="longdash"/>
<label x="-20.32" y="78.74" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="88.9" y1="73.66" x2="91.44" y2="73.66" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="73.66" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="DC_OUT" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="-22.86" y1="73.66" x2="-20.32" y2="73.66" width="0.1524" layer="91" style="longdash"/>
<label x="-20.32" y="73.66" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="AC_OUT" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="-22.86" y1="71.12" x2="-20.32" y2="71.12" width="0.1524" layer="91" style="longdash"/>
<label x="-20.32" y="71.12" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="-5V" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="-22.86" y1="68.58" x2="-20.32" y2="68.58" width="0.1524" layer="91" style="longdash"/>
<label x="-20.32" y="68.58" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="88.9" y1="68.58" x2="91.44" y2="68.58" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="68.58" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="3V3" class="0">
<segment>
<pinref part="J3" gate="G$1" pin="2"/>
<wire x1="35.56" y1="73.66" x2="38.1" y2="73.66" width="0.1524" layer="91" style="longdash"/>
<label x="38.1" y="73.66" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="J8" gate="G$1" pin="1"/>
<wire x1="88.9" y1="20.32" x2="91.44" y2="20.32" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="20.32" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="UC_AUDIO_OUT" class="0">
<segment>
<pinref part="J4" gate="G$1" pin="4"/>
<wire x1="88.9" y1="76.2" x2="91.44" y2="76.2" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="76.2" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="J5" gate="G$1" pin="4"/>
<wire x1="-83.82" y1="30.48" x2="-81.28" y2="30.48" width="0.1524" layer="91" style="longdash"/>
<label x="-81.28" y="30.48" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="GYRO_SCL" class="0">
<segment>
<pinref part="J5" gate="G$1" pin="2"/>
<wire x1="-83.82" y1="25.4" x2="-81.28" y2="25.4" width="0.1524" layer="91" style="longdash"/>
<label x="-81.28" y="25.4" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="GYRO_SDA" class="0">
<segment>
<pinref part="J5" gate="G$1" pin="1"/>
<wire x1="-83.82" y1="22.86" x2="-81.28" y2="22.86" width="0.1524" layer="91" style="longdash"/>
<label x="-81.28" y="22.86" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="PREAMP_AUDIO_OUT" class="0">
<segment>
<pinref part="J6" gate="G$1" pin="2"/>
<wire x1="-33.02" y1="25.4" x2="-30.48" y2="25.4" width="0.1524" layer="91" style="longdash"/>
<pinref part="J6" gate="G$1" pin="3"/>
<wire x1="-33.02" y1="27.94" x2="-30.48" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<wire x1="-30.48" y1="25.4" x2="-30.48" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<wire x1="-30.48" y1="27.94" x2="-27.94" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<junction x="-30.48" y="27.94"/>
<label x="-27.94" y="27.94" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="POWERAMP_AUDIO_OUT" class="0">
<segment>
<pinref part="J7" gate="G$1" pin="2"/>
<wire x1="25.4" y1="30.48" x2="27.94" y2="30.48" width="0.1524" layer="91" style="longdash"/>
<label x="27.94" y="30.48" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SD_DO" class="0">
<segment>
<pinref part="J8" gate="G$1" pin="5"/>
<wire x1="88.9" y1="30.48" x2="91.44" y2="30.48" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="30.48" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SD_CLK" class="0">
<segment>
<pinref part="J8" gate="G$1" pin="4"/>
<wire x1="88.9" y1="27.94" x2="91.44" y2="27.94" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="27.94" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SD_DI" class="0">
<segment>
<pinref part="J8" gate="G$1" pin="3"/>
<wire x1="88.9" y1="25.4" x2="91.44" y2="25.4" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="25.4" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SD_CS" class="0">
<segment>
<pinref part="J8" gate="G$1" pin="2"/>
<wire x1="88.9" y1="22.86" x2="91.44" y2="22.86" width="0.1524" layer="91" style="longdash"/>
<label x="91.44" y="22.86" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<plain>
<text x="-10.16" y="91.44" size="10.16" layer="97" align="center">Audio-Amplifiers</text>
</plain>
<instances>
<instance part="FRAME4" gate="G$1" x="-139.7" y="-109.22"/>
<instance part="FRAME4" gate="G$2" x="33.02" y="-109.22"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
<sheet>
<plain>
<wire x1="-114.3" y1="66.04" x2="-63.5" y2="66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="66.04" x2="-63.5" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="25.4" x2="-114.3" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="-114.3" y1="25.4" x2="-114.3" y2="66.04" width="0.508" layer="97" style="longdash"/>
<text x="-68.072" y="64.262" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="-55.88" y1="66.04" x2="-5.08" y2="66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="66.04" x2="-5.08" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="25.4" x2="-55.88" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="-55.88" y1="25.4" x2="-55.88" y2="66.04" width="0.508" layer="97" style="longdash"/>
<text x="-9.652" y="64.262" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="2.54" y1="66.04" x2="53.34" y2="66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="66.04" x2="53.34" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="25.4" x2="2.54" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="2.54" y1="25.4" x2="2.54" y2="66.04" width="0.508" layer="97" style="longdash"/>
<text x="48.768" y="64.262" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="60.96" y1="66.04" x2="111.76" y2="66.04" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="66.04" x2="111.76" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="25.4" x2="60.96" y2="25.4" width="0.508" layer="97" style="longdash"/>
<wire x1="60.96" y1="25.4" x2="60.96" y2="66.04" width="0.508" layer="97" style="longdash"/>
<text x="107.188" y="64.262" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="-114.3" y1="17.78" x2="-63.5" y2="17.78" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="17.78" x2="-63.5" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="-22.86" x2="-114.3" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="-114.3" y1="-22.86" x2="-114.3" y2="17.78" width="0.508" layer="97" style="longdash"/>
<text x="-68.072" y="16.002" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="-55.88" y1="17.78" x2="-5.08" y2="17.78" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="17.78" x2="-5.08" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="-22.86" x2="-55.88" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="-55.88" y1="-22.86" x2="-55.88" y2="17.78" width="0.508" layer="97" style="longdash"/>
<text x="-9.652" y="16.002" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="2.54" y1="17.78" x2="53.34" y2="17.78" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="17.78" x2="53.34" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="-22.86" x2="2.54" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="2.54" y1="-22.86" x2="2.54" y2="17.78" width="0.508" layer="97" style="longdash"/>
<text x="48.768" y="16.002" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="60.96" y1="17.78" x2="111.76" y2="17.78" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="17.78" x2="111.76" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="-22.86" x2="60.96" y2="-22.86" width="0.508" layer="97" style="longdash"/>
<wire x1="60.96" y1="-22.86" x2="60.96" y2="17.78" width="0.508" layer="97" style="longdash"/>
<text x="107.188" y="16.002" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="-114.3" y1="-30.48" x2="-63.5" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="-30.48" x2="-63.5" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="-63.5" y1="-71.12" x2="-114.3" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="-114.3" y1="-71.12" x2="-114.3" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<text x="-68.072" y="-32.258" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="-55.88" y1="-30.48" x2="-5.08" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="-30.48" x2="-5.08" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="-5.08" y1="-71.12" x2="-55.88" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="-55.88" y1="-71.12" x2="-55.88" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<text x="-9.652" y="-32.258" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="2.54" y1="-30.48" x2="53.34" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="-30.48" x2="53.34" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="53.34" y1="-71.12" x2="2.54" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="2.54" y1="-71.12" x2="2.54" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<text x="48.768" y="-32.258" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
<wire x1="60.96" y1="-30.48" x2="111.76" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="-30.48" x2="111.76" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="111.76" y1="-71.12" x2="60.96" y2="-71.12" width="0.508" layer="97" style="longdash"/>
<wire x1="60.96" y1="-71.12" x2="60.96" y2="-30.48" width="0.508" layer="97" style="longdash"/>
<text x="107.188" y="-32.258" size="5.08" layer="97" rot="R180" align="center">Micro-USB </text>
</plain>
<instances>
<instance part="SUPPLY2" gate="GND" x="-104.14" y="30.48"/>
<instance part="SUPPLY3" gate="GND" x="-45.72" y="30.48"/>
<instance part="SUPPLY4" gate="GND" x="12.7" y="30.48"/>
<instance part="SUPPLY5" gate="GND" x="71.12" y="30.48"/>
<instance part="SUPPLY6" gate="GND" x="-104.14" y="-17.78"/>
<instance part="SUPPLY7" gate="GND" x="-45.72" y="-17.78"/>
<instance part="SUPPLY8" gate="GND" x="12.7" y="-17.78"/>
<instance part="SUPPLY9" gate="GND" x="71.12" y="-17.78"/>
<instance part="SUPPLY10" gate="GND" x="-104.14" y="-66.04"/>
<instance part="SUPPLY11" gate="GND" x="-45.72" y="-66.04"/>
<instance part="SUPPLY12" gate="GND" x="12.7" y="-66.04"/>
<instance part="SUPPLY13" gate="GND" x="71.12" y="-66.04"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
