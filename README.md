[TOC]

# 动画设计规范

## 起步动画（Start）

+ 角色未开始移动时，根骨骼要位于世界坐标原点
+ 起步动画全过程，角色要逐渐加速到步幅完全匹配对应方向的“循环动画（Loop）”的步幅

## 停步动画（Stop）

+ 角色在动画起始阶段的步幅要匹配对应方向的“循环动画（Loop）”的步幅
+ 停步动画全过程，从角色停在原地开始，直到回到Idle状态动画结束播放，根骨骼要位于世界坐标原点

## 回转动画（Pivot）

+ 角色在动画起始阶段的步幅要匹配对应方向的“循环动画（Loop）”的步幅
+ 回转动画的起始阶段，即角色从某个方向移动减速到停在原地，停在原地时，根骨骼要位于世界坐标原点
+ 回转动画的中间阶段，即角色从停在原地并准备往起始移动方向的反方向移动前，根骨骼要位于世界坐标原点
+ 回转动画的结束阶段，即角色向起始移动方向的反方向移动，角色要逐渐加速到步幅完全匹配对应方向的“循环动画（Loop）”的步幅

## 慢跑倾斜Pose（Lean）、加速倾斜动画（Acceleration）

+ 保证角色两脚着地，两脚的间距和慢跑两脚的间距相同

# 空手通用动画（Common）

## 修饰动画（Embellishment）

+ 原地站立Pose：Common_Pose_InPlace
+ 原地蹲伏Pose：Common_Pose_InPlace_Crouch
<br>
+ 身体没有倾斜慢跑Pose：Common_Pose_Jog_Lean_I
+ 身体向前倾斜慢跑Pose：Common_Pose_Jog_Lean_F
+ 身体向后倾斜慢跑Pose：Common_Pose_Jog_Lean_B
+ 身体向左倾斜慢跑Pose：Common_Pose_Jog_Lean_L
+ 身体向右倾斜慢跑Pose：Common_Pose_Jog_Lean_R
<br>
+ 向前慢跑加速倾斜：Common_Jog_Accelerate_F
+ 向后慢跑加速倾斜：Common_Jog_Accelerate_B
+ 向左慢跑加速倾斜：Common_Jog_Accelerate_L
+ 向右慢跑加速倾斜：Common_Jog_Accelerate_R
<br>
+ 向前慢跑倾斜成向前奔跑：Common_Jog_To_Run_Impulse

## 原地动画（InPlace）

+ 原地站立：Common_InPlace_Idle
+ 原地蹲伏：Common_InPlace_Crouch_Idle
<br>
+ 向下蹲：Common_InPlace_SquatDown
+ 站起来：Common_InPlace_StandUp
<br>
+ 原地站立-向左转90°：Common_InPlace_Turn_L90
+ 原地站立-向右转90°：Common_InPlace_Turn_R90
<br>
+ 原地蹲伏-向左转90°：Common_InPlace_Crouch_Turn_L90
+ 原地蹲伏-向右转90°：Common_InPlace_Crouch_Turn_R90

## 站立移动动画 - 静步慢走（Walk）

+ 开始向前：Common_Walk_F_Start
+ 一直向前：Common_Walk_F_Loop
+ 结束向前：Common_Walk_F_Stop
+ 向前时不转身朝反方向走：Common_Walk_F_Pivot
<br>
+ 开始向后：Common_Walk_B_Start
+ 一直向后：Common_Walk_B_Loop
+ 结束向后：Common_Walk_B_Stop
+ 向后时不转身朝反方向走：Common_Walk_B_Pivot
<br>
+ 开始向左前：Common_Walk_F_L_Start
+ 一直向左前：Common_Walk_F_L_Loop
+ 结束向左前：Common_Walk_F_L_Stop
+ 向左前时不转身朝反方向走：Common_Walk_F_L_Pivot
<br>
+ 开始向左后：Common_Walk_B_L_Start
+ 一直向左后：Common_Walk_B_L_Loop
+ 结束向左后：Common_Walk_B_L_Stop
+ 向左后时不转身朝反方向走：Common_Walk_B_L_Pivot
<br>
+ 开始向右前：Common_Walk_F_R_Start
+ 一直向右前：Common_Walk_F_R_Loop
+ 结束向右前：Common_Walk_F_R_Stop
+ 向右前时不转身朝反方向走：Common_Walk_F_R_Pivot
<br>
+ 开始向右后：Common_Walk_B_R_Start
+ 一直向右后：Common_Walk_B_R_Loop
+ 结束向右后：Common_Walk_B_R_Stop
+ 向右后时不转身朝反方向走：Common_Walk_B_R_Pivot
<br>
+ 向左时不转身朝反方向走：Common_Walk_L_Pivot
+ 向右时不转身朝反方向走：Common_Walk_R_Pivot

## 站立移动动画 - 轻步慢跑（Jog）

+ 开始向前：Common_Jog_F_Start
+ 一直向前：Common_Jog_F_Loop
+ 结束向前：Common_Jog_F_Stop
+ 向前时不转身朝反方向跑：Common_Run_F_Pivot
<br>
+ 开始向后：Common_Jog_B_Start
+ 一直向后：Common_Jog_B_Loop
+ 结束向后：Common_Jog_B_Stop
+ 向后时不转身朝反方向跑：Common_Run_B_Pivot
<br>
+ 开始向左前：Common_Jog_F_L_Start
+ 一直向左前：Common_Jog_F_L_Loop
+ 结束向左前：Common_Jog_F_L_Stop
+ 向左前时不转身朝反方向跑：Common_Run_F_L_Pivot
<br>
+ 开始向左后：Common_Jog_B_L_Start
+ 一直向左后：Common_Jog_B_L_Loop
+ 结束向左后：Common_Jog_B_L_Stop
+ 向左后时不转身朝反方向跑：Common_Run_B_L_Pivot
<br>
+ 开始向右前：Common_Jog_F_R_Start
+ 一直向右前：Common_Jog_F_R_Loop
+ 结束向右前：Common_Jog_F_R_Stop
+ 向右前时不转身朝反方向跑：Common_Run_F_R_Pivot
<br>
+ 开始向右后：Common_Jog_B_R_Start
+ 一直向右后：Common_Jog_B_R_Loop
+ 结束向右后：Common_Jog_B_R_Stop
+ 向右后时不转身朝反方向跑：Common_Run_B_R_Pivot
<br>
+ 向左时不转身朝反方向走：Common_Jog_L_Pivot
+ 向右时不转身朝反方向走：Common_Jog_R_Pivot

## 站立移动动画 - 快步奔跑（Run）

+ 开始向前：Common_Run_Start
+ 一直向前：Common_Run_Loop
+ 结束向前：Common_Run_Stop
+ 奔跑时转身朝反方向跑：Common_Run_Pivot

## 蹲伏移动动画 - 潜行静步慢走（Crouch_Walk）

+ 开始向前：Common_Crouch_Walk_F_Start
+ 一直向前：Common_Crouch_Walk_F_Loop
+ 结束向前：Common_Crouch_Walk_F_Stop
+ 向前时不转身朝反方向走：Common_Crouch_Walk_F_Pivot
<br>
+ 开始向后：Common_Crouch_Walk_B_Start
+ 一直向后：Common_Crouch_Walk_B_Loop
+ 结束向后：Common_Crouch_Walk_B_Stop
+ 向后时不转身朝反方向走：Common_Crouch_Walk_B_Pivot
<br>
+ 开始向左前：Common_Crouch_Walk_F_L_Start
+ 一直向左前：Common_Crouch_Walk_F_L_Loop
+ 结束向左前：Common_Crouch_Walk_F_L_Stop
+ 向左前时不转身朝反方向走：Common_Crouch_Walk_F_L_Pivot
<br>
+ 开始向左后：Common_Crouch_Walk_B_L_Start
+ 一直向左后：Common_Crouch_Walk_B_L_Loop
+ 结束向左后：Common_Crouch_Walk_B_L_Stop
+ 向左后时不转身朝反方向走：Common_Crouch_Walk_B_L_Pivot
<br>
+ 开始向右前：Common_Crouch_Walk_F_R_Start
+ 一直向右前：Common_Crouch_Walk_F_R_Loop
+ 结束向右前：Common_Crouch_Walk_F_R_Stop
+ 向右前时不转身朝反方向走：Common_Crouch_Walk_F_R_Pivot
<br>
+ 开始向右后：Common_Crouch_Walk_B_R_Start
+ 一直向右后：Common_Crouch_Walk_B_R_Loop
+ 结束向右后：Common_Crouch_Walk_B_R_Stop
+ 向右后时不转身朝反方向走：Common_Crouch_Walk_B_R_Pivot
<br>
+ 向左时不转身朝反方向走：Common_Crouch_Walk_L_Pivot
+ 向右时不转身朝反方向走：Common_Crouch_Walk_R_Pivot

## 蹲伏移动动画 - 潜行轻步慢跑（Crouch_Jog）

+ 开始向前：Common_Crouch_Jog_F_Start
+ 一直向前：Common_Crouch_Jog_F_Loop
+ 结束向前：Common_Crouch_Jog_F_Stop
+ 向前时不转身朝反方向走：Common_Crouch_Walk_F_Pivot
<br>
+ 开始向后：Common_Crouch_Jog_B_Start
+ 一直向后：Common_Crouch_Jog_B_Loop
+ 结束向后：Common_Crouch_Jog_B_Stop
+ 向后时不转身朝反方向走：Common_Crouch_Walk_B_Pivot
<br>
+ 开始向左前：Common_Crouch_Jog_F_L_Start
+ 一直向左前：Common_Crouch_Jog_F_L_Loop
+ 结束向左前：Common_Crouch_Jog_F_L_Stop
+ 向左前时不转身朝反方向走：Common_Crouch_Walk_F_L_Pivot
<br>
+ 开始向左后：Common_Crouch_Jog_B_L_Start
+ 一直向左后：Common_Crouch_Jog_B_L_Loop
+ 结束向左后：Common_Crouch_Jog_B_L_Stop
+ 向左后时不转身朝反方向走：Common_Crouch_Walk_B_L_Pivot
<br>
+ 开始向右前：Common_Crouch_Jog_F_R_Start
+ 一直向右前：Common_Crouch_Jog_F_R_Loop
+ 结束向右前：Common_Crouch_Jog_F_R_Stop
+ 向右前时不转身朝反方向走：Common_Crouch_Walk_F_R_Pivot
<br>
+ 开始向右后：Common_Crouch_Jog_B_R_Start
+ 一直向右后：Common_Crouch_Jog_B_R_Loop
+ 结束向右后：Common_Crouch_Jog_B_R_Stop
+ 向右后时不转身朝反方向走：Common_Crouch_Walk_B_R_Pivot
<br>
+ 向左时不转身朝反方向走：Common_Crouch_Jog_L_Pivot
+ 向右时不转身朝反方向走：Common_Crouch_Jog_R_Pivot

# 持有武器动画（WeaponName）

## 单帧Pose（Pose）

+ 原地站立Pose：WeaponName_Pose_InPlace
+ 原地蹲伏Pose：WeaponName_Pose_InPlace_Crouch
<br>
+ 身体没有倾斜慢跑Pose：WeaponName_Pose_Lean_I
+ 身体向前倾斜慢跑Pose：WeaponName_Pose_Lean_F
+ 身体向后倾斜慢跑Pose：WeaponName_Pose_Lean_B
+ 身体向左倾斜慢跑Pose：WeaponName_Pose_Lean_L
+ 身体向右倾斜慢跑Pose：WeaponName_Pose_Lean_R

## 装备/收起武器动画（ArmorTransition）

+ 装备武器：WeaponName_Armored
+ 收起武器：WeaponName_Unarmored