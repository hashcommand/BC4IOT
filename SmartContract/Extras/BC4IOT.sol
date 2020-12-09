pragma solidity >=0.4.22 <0.6.0;
contract BC4IOT {
    
    mapping (address => bytes) public ids ;
    
    mapping (uint8 => address) public adminID ;
    mapping (uint8 => address) public systemID ;
    mapping (uint8 => address) public deviceID ;
    
    function BC4IOT_addSID (uint8 SID) public 
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
    
    function BC4IOT_addEID (uint8 _EID, uint8 _SID, uint256 _r, uint256 _s) public 
    {
        if (bytes(ids[msg.sender]).length != 0)
        {
            revert();
        }
        if (systemID [_SID] != address(0))
        {
            revert();
        }
        if (deviceID [_EID] != address(0))
        {
            revert();
        }
        else 
        {
            bytes memory inputData = BC4IOT_BytesConcat(_SID, _EID, msg.sender) ;
            if (token_Verify (inputData, bytes32(_r), bytes32(_s), systemID[_SID]) == false) {
				revert() ;
			}
            BC4IOT_regEID (msg.sender,_EID, _SID);
        }
        
    }
    
    function  BC4IOT_regEID (address addrs, uint8 _SID, uint8 _EID) public
    {
        ids[addrs] = BC4IOT_bytesConvert1(_SID,_EID);
    }
    
    function BC4IOT_bytesConvert1 (uint8 v1, uint8 v2) internal pure returns (bytes memory) {
		bytes memory res = new bytes(2) ;
		uint i = 0 ;
		res[i++] = byte(v1) ;
		res[i++] = byte(v2) ;
		return res ;
	}
	
	function BC4IOT_BytesConcat (uint8 v1, uint8 v2, address addr) internal pure returns (bytes memory)
	{
	    bytes memory baddr = BC4IOT_FromAddressToBytes(addr) ;
		bytes memory res   = new bytes (1 + 1 + 20) ;
        
		uint i = 0 ;
		res[i++] = byte(v1) ;
		res[i++] = byte(v2) ;
		uint j = 0 ;
		for (j = 0; j < 20; j++)
			res[i++] = baddr[j] ;
	
		return res ;
	}
	
	function BC4IOT_FromAddressToBytes(address a) internal pure returns (bytes memory b ) {
        	assembly {
            		let m := mload(0x40)
			mstore(add(m, 20), xor(0x140000000000000000000000000000000000000000, a))
			mstore(0x40, add(m, 52))
			b := m
         	}
    	}
    	
    function token_Verify (bytes memory inputData, bytes32 _r, bytes32 _s , address SID) internal pure returns (bool)
    	{

        	bytes32 hash = keccak256(inputData) ;
        	uint8   v    = 27 ;

        	if ((ecrecover(hash, v, _r, _s) == SID)) 
            		return true ;
        	else
            		return false ;
	}	
	
	function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]) ;
	}

    
}
