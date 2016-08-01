package flash.text.engine
{
[native(cls="TextBlockClass", methods="auto")]

final public class TextBlock
{
	//Consts
	
	//Properties
//	public native function get applyNonLinearFontScaling() : Boolean
//	public native function set applyNonLinearFontScaling(applyNonLinearFontScaling : Boolean):void
	
//	public native function get baselineFontDescription() : FontDescription
//	public native function set baselineFontDescription(baselineFontDescription : FontDescription):void
	
//	public native function get baselineFontSize() : Number
//	public native function set baselineFontSize(baselineFontSize : Number):void
	
//	public native function get baselineZero() : String
//	public native function set baselineZero(baselineZero : String):void
	
//	public native function get bidiLevel() : int
//	public native function set bidiLevel(bidiLevel : int):void
	
//	public native function get content() : ContentElement
//	public native function set content(content : ContentElement):void
	
//	public native function get firstInvalidLine() : TextLine
	
//	public native function get firstLine() : TextLine
	
//	public native function get lastLine() : TextLine
	
//	public native function get lineRotation() : String
//	public native function set lineRotation(lineRotation : String):void
	
//	public native function get tabStops() : Vector.<TabStop>
//	public native function set tabStops(tabStops : Vector.<TabStop>):void
	
//	public native function get textJustifier() : TextJustifier
//	public native function set textJustifier(textJustifier : TextJustifier):void
	
//	public native function get textLineCreationResult() : String
	
//	public native function get userData() : *
//	public native function set userData(userData : *):void
	
	//Methods
//	public native function TextBlock(content:ContentElement = null, tabStops:Vector.<TabStop> = null, textJustifier:TextJustifier = null, lineRotation:String = "rotate0", baselineZero:String = "roman", bidiLevel:int = 0, applyNonLinearFontScaling:Boolean = true, baselineFontDescription:FontDescription = null, baselineFontSize:Number = 12.0)
//	public native function createTextLine(previousLine:TextLine = null, width:Number = 1000000, lineOffset:Number = 0.0, fitSomething:Boolean = false):TextLine
//	public native function dump():String
//	public native function findNextAtomBoundary(afterCharIndex:int):int
//	public native function findNextWordBoundary(afterCharIndex:int):int
//	public native function findPreviousAtomBoundary(beforeCharIndex:int):int
//	public native function findPreviousWordBoundary(beforeCharIndex:int):int
//	public native function getTextLineAtCharIndex(charIndex:int):TextLine
//	public native function recreateTextLine(textLine:TextLine, previousLine:TextLine = null, width:Number = 1000000, lineOffset:Number = 0.0, fitSomething:Boolean = false):TextLine
//	public native function releaseLineCreationData():void
//	public native function releaseLines(firstLine:TextLine, lastLine:TextLine):void
        public var userData:Object;

        public function TextBlock(content:ContentElement = null, tabStops:Vector.<TabStop> = null, textJustifier:TextJustifier = null, lineRotation:String = "rotate0", baselineZero:String = "roman", bidiLevel:int = 0, applyNonLinearFontScaling:Boolean = true, baselineFontDescription:FontDescription = null, baselineFontSize:Number = 12)
        {
            if (content)
            {
                this.content = content;
            }
            if (tabStops)
            {
                this.tabStops = tabStops;
            }
            this.textJustifier = textJustifier ? (textJustifier) : (TextJustifier.getJustifierForLocale("en"));
            this.lineRotation = lineRotation;
            if (baselineZero)
            {
                this.baselineZero = baselineZero;
            }
            this.bidiLevel = bidiLevel;
            this.applyNonLinearFontScaling = applyNonLinearFontScaling;
            if (baselineFontDescription)
            {
                this.baselineFontDescription = baselineFontDescription;
                this.baselineFontSize = baselineFontSize;
            }
            return;
        }// end function

        public native function get applyNonLinearFontScaling() : Boolean;

        public native function set applyNonLinearFontScaling(value:Boolean) : void;

        public native function get baselineFontDescription() : FontDescription;

        public native function set baselineFontDescription(value:FontDescription) : void;

        public native function get baselineFontSize() : Number;

        public native function set baselineFontSize(value:Number) : void;

        public native function get baselineZero() : String;

        public native function set baselineZero(value:String) : void;

        public native function get content() : ContentElement;

        public native function set content(value:ContentElement) : void;

        public native function get bidiLevel() : int;

        public native function set bidiLevel(value:int) : void;

        public native function get firstInvalidLine() : TextLine;

        public native function get firstLine() : TextLine;

        public native function get lastLine() : TextLine;

        public function get textJustifier() : TextJustifier
        {
            return this.getTextJustifier().clone();
        }// end function

        public function set textJustifier(value:TextJustifier) : void
        {
            var _loc_2:* = value ? (value.clone()) : (null);
            this.setTextJustifier(_loc_2);
            return;
        }// end function

        private native function getTextJustifier() : TextJustifier;

        private native function setTextJustifier(value:TextJustifier) : void;

        public native function get textLineCreationResult() : String;

        public native function get lineRotation() : String;

        public native function set lineRotation(value:String) : void;

        public function get tabStops() : Vector.<TabStop>
        {
            var _loc_3:uint = 0;
            var _loc_4:TabStop = null;
            var _loc_5:TabStop = null;
            var _loc_1:* = this.getTabStops();
            var _loc_2:Vector.<TabStop> = null;
            if (_loc_1)
            {
                _loc_2 = new Vector.<TabStop>;
                _loc_3 = 0;
                while (_loc_3 < _loc_1.length)
                {
                    
                    _loc_4 = _loc_1[_loc_3];
                    _loc_5 = new TabStop(_loc_4.alignment, _loc_4.position, _loc_4.decimalAlignmentToken);
                    _loc_2.push(_loc_4);
                    _loc_3 = _loc_3 + 1;
                }
            }
            return _loc_2;
        }// end function

        public function set tabStops(value:Vector.<TabStop>) : void
        {
            var _loc_3:uint = 0;
            var _loc_4:TabStop = null;
            var _loc_5:TabStop = null;
            var _loc_2:Vector.<TabStop> = null;
            if (value)
            {
                _loc_2 = new Vector.<TabStop>;
                _loc_3 = 0;
                while (_loc_3 < value.length)
                {
                    
                    _loc_4 = value[_loc_3];
                    _loc_5 = new TabStop(_loc_4.alignment, _loc_4.position, _loc_4.decimalAlignmentToken);
                    _loc_2.push(_loc_4);
                    _loc_3 = _loc_3 + 1;
                }
            }
            this.setTabStops(_loc_2);
            return;
        }// end function

        private native function getTabStops() : Vector.<TabStop>;

        private native function setTabStops(value:Vector.<TabStop>) : void;

        public native function findNextAtomBoundary(afterCharIndex:int) : int;

        public native function findPreviousAtomBoundary(beforeCharIndex:int) : int;

        public native function findNextWordBoundary(afterCharIndex:int) : int;

        public native function findPreviousWordBoundary(beforeCharIndex:int) : int;

        public native function getTextLineAtCharIndex(charIndex:int) : TextLine;

        public function createTextLine(previousLine:TextLine = null, width:Number = 1000000, lineOffset:Number = 0, fitSomething:Boolean = false) : TextLine
        {
            if (this.content == null)
            {
                return null;
            }
            if (previousLine != null)
            {
            
				if (previousLine.validity != TextLineValidity.VALID)
				{
					Error.throwError(ArgumentError, 2004, "previousLine");
				}
			}
            if (previousLine != null)
            {
            
				if (previousLine.textBlock != this)
				{
					Error.throwError(ArgumentError, 2004, "previousLine");
				}
			}
            if (width < 0)
            {
	            if (fitSomething != false)
	            {
		            if (width > TextLine.MAX_LINE_WIDTH)
					{
						Error.throwError(ArgumentError, 2004, "width");
					}
				}            
            }
            if (width == 0)
            {
            
				if (fitSomething == false)
				{
					return null;
				}
			}
            return this.DoCreateTextLine(previousLine, width, lineOffset, fitSomething, null);
        }// end function

        public function recreateTextLine(textLine:TextLine, previousLine:TextLine = null, width:Number = 1000000, lineOffset:Number = 0, fitSomething:Boolean = false) : TextLine
        {
            if (textLine == null)
            {
                Error.throwError(ArgumentError, 2004, "textLine");
            }
            if (previousLine != null)
            {
				if (previousLine.validity != TextLineValidity.VALID)
				{
					Error.throwError(ArgumentError, 2004, "previousLine validity");
				}
			
				if (previousLine.textBlock != this)
				{
					Error.throwError(ArgumentError, 2004, "previousLine block");
				}
			
				if (previousLine == textLine)
				{
					Error.throwError(ArgumentError, 2004, "previousLine textLine");
				}
			}
            if (width < 0)
            {
				if (fitSomething != false)
				{
					if (width > TextLine.MAX_LINE_WIDTH)
					{
						Error.throwError(ArgumentError, 2004, "width");
					}
				}
			}
            textLine.userData = null;
            return this.DoCreateTextLine(previousLine, width, lineOffset, fitSomething, textLine);
        }// end function

        private native function DoCreateTextLine(previousLine:TextLine, width:Number, lineOffset:Number = 0, fitSomething:Boolean = false, reuseLine:TextLine = null) : TextLine;

        public native function releaseLineCreationData() : void;

        public native function releaseLines(firstLine:TextLine, lastLine:TextLine) : void;

        public native function dump() : String;
}
}