pragma solidity ^0.5.0;

contract BC4IOT {
    
    mapping (address => bytes) public ids;
    
    function addSID(uint8 _SID) public {
        if( bytes(ids[msg.sender]).length != 0 )
        {
            revert("ID Already Exists");
        }
        BC4IOT_SaveFogNode(msg.sender, _SID);
	}
	
	function BC4IOT_SaveFogNode(address _addr, uint8 _SID) public {
		ids[_addr] = BC4IOT_Concat2Bytes(_SID) ;
	}
	
	function BC4IOT_Concat2Bytes (uint8 v1) internal pure returns (bytes memory) {
		bytes memory res = new bytes(1) ;
		uint i = 0 ;
		res[i++] = byte(v1) ;
		return res ;
	}
  
    function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]) ;
	}
	
}












