/********************/装饰器/************************************************************/
//@State
组件中的状态变量，状态变量变化会触发UI刷新，即 build() 中使用到该 @State变量 的UI组件会重新渲染。

注意：嵌套变量中内层变量属性的变化不会被观察到，因此不会引起UI刷新。比如嵌套的object和class。


//@Prop
父组件变量 >> 子组件变量 的单向同步
用父组件变量（数据源）对子组件的@Prop变量进行初始化，当数据源发生变化时，@Prop变量也会发生变化，刷新UI组件。
@Component
struct ChildComponent {
	@Prop name : string;

	build() {}
}

@Entry
@Component
struct ParentComponent {
	@State ParentName : string = "LiHua";
		build() {
		ChildComponent({ name: this.ParentName })
	}
}


//@Link
父组件变量 << >> 子组件变量 的双向同步
@Component
struct ChildComponent {
	@Link name : string;

	build() {}
}

@Entry
@Component
struct ParentComponent {
	@State ParentName : string = "LiHua";
	build() {
		ChildComponent({ name: this.ParentName })
	}
}


//@Provide / @Consume
与@Prop不同的是，@Provide / @Consume支持更多层级组件之间传递参数，支持子孙组件直接接受到祖先组件的参数，解决父组件参数需要在子组件之间依次传递参数的问题；
@Component
struct ChildSonComponent {
	@Consume name : string;

	build() {}
}

@Component
struct ChildComponent {
	build() {
		ChildSonComponent()
	}
}

@Entry
@Component
struct ParentComponent {
	@Provide ParentName : string = "LiHua";
		build() {
		ChildComponent()
	}
}


// 通过相同的变量名绑定
@Provide age : number = 0;
@Consume age : number;

// 通过相同的变量别名绑定
@Provide('a') id: number = 0;
@Consume('a') age: number;


//$$
父组件变量 << >> 子组件（系统内置组件）变量 的双向同步


//@Watch
@Watch可以为@State、@Prop等状态变量设置回调函数，在变量发生变化时触发该回调

@State @Watch('change') num: number = 10;
change() {
	console.log(`xxx`);
}


//@Track
用于修饰class的属性，@Track装饰的属性发生变化，该属性关联的UI触发更新
class LogTrack {
	@Track str : string = '';
}

@Entry
@Component
struct AddLog {
	@State logTrack : LogTrack = new LogTrack();

	build() {
		Text(this.logTrack.str1)
	}
}

