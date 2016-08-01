﻿package adobe.utils
{
    import flash.events.*;

    final public class ProductManager extends EventDispatcher
    {

        public native function ProductManager(name:String = null, shared:Boolean = false)


        public native function get running() : Boolean;

        public native function get installed() : Boolean;

        public native function launch(parameters:String = null) : Boolean;

        public native function get installedVersion() : String;

        public function download(caption:String = null, fileName:String = null, pathElements:Array = null) : Boolean
        {
            var _loc_5:uint = 0;
            var _loc_6:uint = 0;
            var _loc_4:String = null;
            if (fileName != null)
            {
                _loc_4 = new String();
                if (pathElements != null)
                {
                    _loc_5 = pathElements.length;
                    _loc_6 = 0;
                    while (_loc_6 < _loc_5)
                    {
                        
                        _loc_4 = _loc_4 + (this.validate(pathElements[_loc_6]) + "/");
                        _loc_6 = _loc_6 + 1;
                    }
                }
                _loc_4 = _loc_4 + this.validate(fileName);
            }
            return this.doDownload(caption, _loc_4);
        }// end function

        private native function doDownload(caption:String, fileName:String) : Boolean;

        private function validate(str:String) : String
        {
            var _loc_2:String = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-_";
            var _loc_3:* = str.length;
            var _loc_4:uint = 0;
            while (_loc_4 < _loc_3)
            {
                
                if (_loc_2.indexOf(str.charAt(_loc_4)) == -1)
                {
                    throw new ArgumentError();
                }
                _loc_4 = _loc_4 + 1;
            }
            return str;
        }// end function

        public native function doSelfUpgrade(os:String) : Boolean;

    }
}
