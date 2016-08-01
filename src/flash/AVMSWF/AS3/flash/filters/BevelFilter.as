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

package flash.filters
{
	[native(cls="BevelFilterClass", methods="auto")]

	import flash.filters.BitmapFilter

	public final class BevelFilter extends  BitmapFilter
	{
		//Properties
		 public var angle:Number;
		 public var blurX:Number;
		 public var blurY:Number;
		 public var distance:Number;
		 public var highlightAlpha:Number;
		 public var highlightColor:uint;
		 public var knockout:Boolean;
		 public var quality:int;
		 public var shadowAlpha:Number;
		 public var shadowColor:uint;
		 public var strength:Number;
		 public var type:String;
		 		 
		//Methods
		 public function BevelFilter(distance:Number = 4.0, angle:Number = 45, highlightColor:uint = 0xFFFFFF, highlightAlpha:Number = 1.0, 
								shadowColor:uint = 0x000000, shadowAlpha:Number = 1.0, blurX:Number = 4.0, blurY:Number = 4.0, 
								strength:Number = 1, quality:int = 1, type:String = "inner", knockout:Boolean = false) 
		{
			this.angle=angle;
			this.blurX=blurX;
			this.blurY=blurY;
			this.distance=distance;
			this.highlightAlpha=highlightAlpha;
			this.highlightColor=highlightColor;
			this.knockout=knockout;
			this.quality=quality;
			this.shadowAlpha=shadowAlpha;
			this.shadowColor=shadowColor;
			this.strength=strength;
			this.type=type;
		}
		 public override function clone():BitmapFilter 
		 {
			return new BevelFilter(distance,angle,highlightColor,highlightAlpha,
								   shadowColor,shadowAlpha,blurX,blurY,
								   strength,quality,type,knockout);
		 }
	}
}
