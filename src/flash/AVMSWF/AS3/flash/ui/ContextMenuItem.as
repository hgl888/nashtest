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

package flash.ui
{
	[native(cls="ContextMenuItemClass", methods="auto")]

	import flash.events.EventDispatcher

	public final class ContextMenuItem extends  EventDispatcher
	{
		//Properties
		 public var caption:String;
		 public var enabled:Boolean;
		 public var separatorBefore:Boolean;
		 //public var visible:Boolean;
		 
		//Methods
		 public function ContextMenuItem(caption:String, separatorBefore:Boolean = false, enabled:Boolean = true, visible:Boolean = true)
		 {
			this.caption=caption;
			this.enabled=enabled;
			this.separatorBefore=separatorBefore;
			this.visible=visible;
		 }

		 public function clone():ContextMenuItem
		 {
			var newItem:ContextMenuItem=new ContextMenuItem(caption,enabled,separatorBefore,visible);
			return newItem;
		 }

		public native function get visible() : Boolean 
		public native function set visible(bvis : Boolean): void
		 //new adds
		public native static function systemClearMenuItem():ContextMenuItem
		public native static function systemCopyLinkMenuItem():ContextMenuItem
		public native static function systemCopyMenuItem():ContextMenuItem
		public native static function systemCutMenuItem():ContextMenuItem
		public native static function systemOpenLinkMenuItem():ContextMenuItem
		public native static function systemPasteMenuItem():ContextMenuItem
		public native static function systemSelectAllMenuItem():ContextMenuItem
		 //new adds end
	}
}
