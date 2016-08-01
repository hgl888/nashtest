/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe  Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

 package flash.geom
 {
 	[native(cls="ColorTransformClass", methods="auto")]

 	public class ColorTransform
 	{
 		//Properties
 		public var alphaMultiplier : Number = 1;//�� Alpha ͸����ͨ��ֵ��˵�ʮ����ֵ�� ColorTransform 
		public var alphaOffset : Number=0;//-255 �� 255 ֮������֣������� alphaMultiplier ֵ��ˣ����� Alpha ͸����ͨ��ֵ��ӡ� ColorTransform 
		public var blueMultiplier : Number =1;//����ɫͨ��ֵ��˵�ʮ����ֵ�� ColorTransform 
		public var blueOffset : Number = 0;//-255 �� 255 ֮������֣������� blueMultiplier ֵ��ˣ�������ɫͨ��ֵ��ӡ� ColorTransform 
		public var greenMultiplier : Number = 1;//����ɫͨ��ֵ��˵�ʮ����ֵ�� ColorTransform 
		public var greenOffset : Number = 0;//-255 �� 255 ֮������֣������� greenMultiplier ֵ��ˣ�������ɫͨ��ֵ��ӡ� ColorTransform 
		public var redMultiplier : Number = 1;//���ɫͨ��ֵ��˵�ʮ����ֵ�� ColorTransform 
		public var redOffset : Number =0;

		public function ColorTransform(redMultiplier:Number = 1.0, greenMultiplier:Number = 1.0, blueMultiplier:Number = 1.0, alphaMultiplier:Number = 1.0, redOffset:Number = 0, greenOffset:Number = 0, blueOffset:Number = 0, alphaOffset:Number = 0)
		{
			this.redMultiplier=redMultiplier;
			this.greenMultiplier=greenMultiplier;
			this.blueMultiplier=blueMultiplier;
			this.alphaMultiplier=alphaMultiplier;
			this.redOffset=redOffset;
			this.greenOffset=greenOffset;
			this.blueOffset=blueOffset;
			this.alphaOffset=alphaOffset;
		}
		public native function get color() : uint
		public native function set color(newColor : uint)

		
 		//Methods
 		 
 		 public native function concat(second:ColorTransform):void;
 		 public native function toString():String;
 		 /*{
 			var str:String="(redMultiplier=";
 			str+=String(redMultiplier);
 			str+=",greenMultiplier=";
 			str+=String(greenMultiplier);
 			
 			str+=",blueMultiplier=";
 			str+=String(blueMultiplier);
 			
 			str+=",alphaMultiplier=";
 			str+=String(alphaMultiplier);
 			
 			str+=",redOffset=";
 			str+=String(redOffset);
 			
 			str+=",greenOffset=";
 			str+=String(greenOffset);
 			
 			str+=",blueOffset=";
 			str+=String(blueOffset);
 			
 			str+=",alphaOffset=";
 			str+=String(alphaOffset);
 			
 			str+=")";
 			return str;
 		 }*/
 	}
 }
