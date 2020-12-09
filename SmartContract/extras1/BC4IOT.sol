pragma solidity >=0.4.22 <0.6.0;
contract BC4IOT {
    
    mapping (address => bytes) public ids ;
    
    mapping (uint8 => address) public systemID ;
    mapping (uint8 => address) public deviceID ;
    
    function BC4IOT_addSID (uint8 SID) external 
    {
        if (bytes(ids[msg.sender]).length != 0)
        {
            revert();
        }
        if (systemID [SID] != address(0))
        {
            revert();
        }
        else 
        {
            BC4IOT_regSID (msg.sender , SID);
        }
        
    }
    
    function  BC4IOT_regSID (address addrs, uint8 systemid) public
    {
        ids[addrs] = BC4IOT_bytesConvert(systemid);
    }
    
    function BC4IOT_bytesConvert (uint8 v1) internal pure returns (bytes memory) {
		bytes memory res = new bytes(2) ;
		uint i = 0 ;
		res[i++] = byte(v1) ;
		return res ;
	}
    

    function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]) ;
	}
}
