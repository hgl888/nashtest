package flash.accessibility
{
	import flash.geom.Rectangle;
	[native(cls="ISearchableTextClass",methods="auto")]
	public interface ISearchableText
	{
		function get searchText():String
	}
	[native(cls="ISimpleTextSelection",method="auto")]
	public interface ISimpleTextSelection
	{
		function get selectionActiveIndex():int
		function get selectionAnchorIndex():int
	}
	[native(cls="AccessibilityImplementationClass", methods="auto")]
	public class AccessibilityImplementation extends Object
	{
		  public var errno:uint = 0
		  public var stub:Boolean = false
		  //��̬���캯��
		  public function accDoDefaultAction(childID:uint):void
		  {
		  }
		  //һ�� IAccessible ������ִ����� AccessibilityImplementation ��ʾ�����������Ĭ�ϲ�������ִ�и��������Ԫ��֮һ��Ĭ�ϲ����� AccessibilityImplementation 
		  public function accLocation(childID:uint):*
		  {
			return null;
		  }
		  //MSAA ����������ָ�� AccessibilityImplementation ����Ԫ�ر߿�� DisplayObject �� Rectangle�� AccessibilityImplementation 
		  public function accSelect(operation:uint, childID:uint):void
		  {
		  }
		  //IAccessible ���������Ĵ� AccessibilityImplementation ����ʾ����е�ѡ�����ݡ� AccessibilityImplementation 
		  public function get_accDefaultAction(childID:uint):String
		  {
		    return null;
		  }
		  //MSAA ���������ش� AccessibilityImplementation ����ʾ�����Ĭ�ϲ���������������Ԫ��֮һ��Ĭ�ϲ����� AccessibilityImplementation 
		  public function get_accFocus():uint
		  {
			return 0;
		  }
		  //MSAA ����������������ھ����ӽ������Ԫ�أ�����У����޷������� ID�� AccessibilityImplementation 
		  public function get_accName(childID:uint):String
		  {
			return null;
		  }
		  //MSAA ���������ش� AccessibilityImplementation ����ʾ��������ƻ������Ԫ��֮һ�����ơ� AccessibilityImplementation 
		  public function get_accRole(childID:uint):uint
		  {
			return 0;
		  }
		 //MSAA ���������ش� AccessibilityImplementation ����ʾ��������ƻ������Ԫ��֮һ��ϵͳ��ɫ�� AccessibilityImplementation 
		  public function get_accSelection():Array
		  {
			return new Array(0);
		  }
		  //MSAA ���������ذ���ȫ����ѡ��Ԫ�ص� ID �����顣 AccessibilityImplementation 
		  public function get_accState(childID:uint):uint
		  {
			return 0;
		  }
		   //IAccessible ���������ش� AccessibilityImplementation ����ʾ����ĵ�ǰ����ʱ״̬������������Ԫ��֮һ�ĵ�ǰ����ʱ״̬�� AccessibilityImplementation 
		  public function get_accValue(childID:uint):String
		  {
			return null;
		  }
		  //MSAA ���������ش� AccessibilityImplementation ����ʾ���������ʱֵ������������Ԫ��֮һ������ʱֵ�� AccessibilityImplementation 
		  public function getChildIDArray():Array
		  {
			return new Array(0);
		  }
		  //����һ�����飬���а��� AccessibilityImplementation ��������Ԫ�ص��޷������� ID�� AccessibilityImplementation 
		  public function hasOwnProperty(name:String):Boolean
		  {
			return false;
		  }
		 //ָʾ�����Ƿ��Ѿ�������ָ�������ԡ� Object 
		  public function isLabeledBy(labelBounds:Rectangle):Boolean
		  {
			return false;
		  }
		  //���� true �� false����ָʾ�߿��� x��y��width �� height ָ�����ı������Ƿ�Ӧ����Ϊ AccessibilityImplementation ��ʾ������ı�ǩ 

	}
}

package flash.display
{
	public interface IGraphicsData 
	{
	}
	public interface IGraphicsFill 
	{
	}
	public interface IGraphicsPath
	{
	}
	public interface IGraphicsStroke
	{
	}
	public final class ColorCorrection extends Object
	{
		//ColorCorrection ���Ϊ flash.display.Stage.colorCorrection �����ṩֵ�� 

		public static var DEFAULT : String = "default"//[��̬] ʹ��������Ĭ����ɫУ���� ColorCorrection 
		public static var OFF : String = "off"//[��̬] �ر���ɫУ�������۲���������������Ρ� ColorCorrection 
		public static var ON : String = "on"//[��̬] ����ɫУ�������۲�������������������У���Ρ� 
	}
	public final class ColorCorrectionSupport extends Object
	{//ColorCorrectionSupport ���Ϊ flash.display.Stage.colorCorrectionSupport �����ṩֵ�� 
		public static var DEFAULT_OFF : String = "defaultOff"//[��̬] ֧����ɫУ����Ĭ�������Ϊ�ر�״̬�� ColorCorrectionSupport 
		public static var DEFAULT_ON : String = "defaultOn"//[��̬] ֧����ɫУ����Ĭ�������Ϊ��״̬�� ColorCorrectionSupport 
		public static var UNSUPPORTED : String = "unsupported"//[��̬] ����������֧����ɫУ���� 
	}

}
