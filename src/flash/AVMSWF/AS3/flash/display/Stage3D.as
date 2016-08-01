/*
	Stage3D���ṩһ����ʾ����Ϳɱ����Ⱦ�����������ڻ��� 2D �� 3D ͼ�Ρ�
	Stage3D ʹ�� Context3D �๩��Ⱦ������ʵ�ָ����ܵ���Ⱦ���档�ڿ��ܵ�����£�
	�˱���ʹ��ͼ�δ���Ԫ (GPU)������ʱ��̨�ṩ�̶���Ŀ�� Stage3D ����
	ʵ������Ŀ�����豸���͵Ĳ�ͬ��������ͬ����������ͨ���ṩ�ĸ� Stage3D ʵ����
*/
  package flash.display
  {
	[native(cls="Stage3DClass", methods="auto")]

	import flash.events.EventDispatcher
	import flash.display3D.Context3D

	
	public class Stage3D extends EventDispatcher
	{
		//Properties
		//public native function get context3D():Context3D
		
		public native function get visible(): Boolean
		public native function set visible(value:Boolean):void

		public native function get x():Number
		public native function set x(value:Number):void

		public native function get y():Number
		public native function set y(value:Number):void

		//Methods
		public function Stage3D()
		{
			return;
		}//end function

		//public native function requestContext3D(context3DRenderMode:String = "auto",  profile:String = "baseline"):void

	}
}