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

 package BWLoader
 {
 
 	[native(cls="BwExternAPIClass",instance="BwExternAPIObject",methods="auto")]
	import flash.utils.ByteArray;

 	public class BwExternAPI
 	{
 	
 		 public function BwExternAPI() {}
 		 
 		static public native function GetBwExternAPIObj() : BwExternAPI
 		//Properties
 		
 		 public native function getDeviceType() : String
 		 
 		 public native function getHPixel() : int
 		 
 		 public native function getVPixel() : int
 		 
 		 public native function getDPI() : int
 		 
 		 //ͨ��SDK�����û�ע��
 		 //Type	����	1Ϊ��Ϸ���ƽ��棬2Ϊʹ��SDK����
 		 //User_Name	�ַ���	�û���
 		 //Password	�ַ���	����
 		 //Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function SDKRegister(type:int, username:String, passwd:String ):int
 		 
 		 
 		 //ͨ��SDK�����û���¼
 		 //Type	����	1Ϊ��Ϸ���ƽ��棬2Ϊʹ��SDK����
		//User_Name	�ַ���	�û���
		//Password	�ַ���	����
		//Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function SDKLogin( type:int, username:String, passwd:String ):int
 		 
 		 //ͨ��SDK�����û��˳�		
 		 //Type	����	1Ϊ��Ϸ���ƽ��棬2Ϊʹ��SDK����
 		 //User_Name	�ַ���	�û���
 		 public native function SDKLogout( type:int, username:String ):int
 		 
 		 //Type	����	1Ϊ��Ϸ���ƽ��棬2Ϊʹ��SDK����
 		 //User_Name	�ַ���	�û���
 		 //Password	�ַ���	����
 		 //Amount	����	֧�����
 		 //Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function SDKPayment( type:int, username:String, passwd:String, amount:int ):int
 		 
 		 //Data_Name	�ַ���	��������
 		 //Data_String	�����ƴ�	��������
 		 //Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function SaveDisk( dataName:String, dataString:ByteArray ) : int
 		 
 		 //�ӿͻ��˶�ȡ���������		
 		 //Data_Name	�ַ���	��������
 		 //Data_String	�����ƴ�	��������
 		 public native function LoadDisk( dataName:String ) : String
 		 
 		 //�����ڴ棬������ָ��URL		
 		 //Type	����	1ΪSWF��2Ϊ��ҳ
 		 //URL	�ַ���	�����ĵ�ַ
 		 //Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function Launch( type:int, url:String ) : int
 		 
 		 //֪ͨ�ͻ��˱�SWF�Ƿ���Ҫʹ�ò�����������		
 		 //visible	����	0Ϊ��ʾ��1Ϊ����
 		 //Result	����	0000Ϊ�ɹ�������Ϊ������
 		 public native function ShowToolbar( visible :int ) : int 
 		 
 		 //�ر�FLASH
 		 public native function CloseSwf()
 	
 	}
 }