package flash.security
{
    [native(cls="X509CertificateClass", methods="auto")]

    import flash.utils.*;

    public class X509Certificate
    {

        public function X509Certificate()
        {
            return;
        }// end function

        public native function get version() : uint;

        public native function get serialNumber() : String;

        public native function get signatureAlgorithmOID() : String;

        public native function get signatureAlgorithmParams() : ByteArray;

        public native function get issuer() : X500DistinguishedName;

        public native function get validNotBefore() : Date;

        public native function get validNotAfter() : Date;

        public native function get subject() : X500DistinguishedName;

        public native function get subjectPublicKeyAlgorithmOID() : String;

        public native function get subjectPublicKey() : String;

        public native function get issuerUniqueID() : String;

        public native function get subjectUniqueID() : String;

        public native function get encoded() : ByteArray;

    }
}
