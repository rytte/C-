//导入HarmonyOS SDK的开放能力

HarmonyOS SDK提供的开放能力（接口）也需要在导入声明后使用。可直接导入接口模块来使用该模块内的所有接口能力，例如：

import UIAbility from '@ohos.app.ability.UIAbility';
从HarmonyOS NEXT Developer Preview 1版本开始引入Kit概念。SDK对同一个Kit下的接口模块进行了封装，开发者在示例代码中可通过导入Kit的方式来使用Kit所包含的接口能力。其中，Kit封装的接口模块可查看SDK目录下Kit子目录中各Kit的定义。

通过导入Kit方式使用开放能力有三种方式：

方式一：导入Kit下单个模块的接口能力。例如：
import { UIAbility } from '@kit.AbilityKit';

方式二：导入Kit下多个模块的接口能力。例如：
import { UIAbility, Ability, Context } from '@kit.AbilityKit';

方式三：导入Kit包含的所有模块的接口能力。例如：
import * as module_name from '@kit.AbilityKit';

其中，“module_name”为别名，可自定义，然后通过该名称调用模块的接口。





//ArkTS中禁止使用any类型



//禁止在运行时变更对象布局
1、禁止 向对象中添加新的属性或方法。
2、禁止 从对象中删除已有的属性或方法。
3、禁止 将任意类型的值赋值给对象属性。	

