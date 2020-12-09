pragma solidity ^0.5.1;

contract BC4IOT {
    
    mapping (address => bytes) public ids ;
    
    mapping (uint8 => address) public systemID ;
    mapping (uint8 => address) public deviceID ;
    
    // System Registration
    function addSID (uint8 _SID) public 
    {
        if (bytes(ids[msg.sender]).length != 0)
        {
            revert("Fog Node Already Registered");
        }
        if (systemID [_SID] != address(0))
        {
            revert("This SID already Registered");
        }
        else 
        {
            systemID [_SID] = msg.sender;
        }
    }
    
    function BC4IOT_bytesConvert (uint8 v1) public pure returns (bytes memory) {
		bytes memory res = new bytes(1) ;
		uint i = 0 ;
		res[i++] = byte(v1) ;
		return res ;
	}
	
	// Device Registration
    function addEID (uint8 _EID, uint8 _SID, uint256 hash, uint256 r, uint256 s) public 
    {
        
        if (bytes(ids[msg.sender]).length != 0)
        {
            revert("This Node Already Exists");
        }
        if (deviceID [_EID] != address(0))
        {
            revert("This Device already Registered");
        }
        else 
        {
            if (token_Verify (bytes32 (hash), bytes32 (r), bytes32 (s)) !=  systemID[_SID]) 
            {
				revert("Verification Failed") ;
		    }
			
			deviceID [_EID] = msg.sender;
            BC4IOT_regEID (_EID,_SID,msg.sender);
        }
    }
    function  BC4IOT_regEID (uint8 _SID, uint8 _EID, address addrs) public
    {
        ids[addrs] = BC4IOT_bytesConvert1(_SID,_EID);
    }
    
    function BC4IOT_bytesConvert1 (uint8 v1, uint8 v2) public pure returns (bytes memory) 
    {
 	    bytes memory res = new bytes(2) ;
 		uint i = 0 ;
 		res[i++] = byte(v1) ;
 		res[i++] = byte(v2) ;
 		return res ;
 	}
	
	// token_verification
	function token_Verify (bytes32 hash, bytes32 r, bytes32 s) public pure returns (address)
    {
        //bytes32 r;
        //bytes32 s;
        uint8 v = 27;
        
        bytes32 prefixedHash = keccak256(abi.encodePacked("\x19Ethereum Signed Message:\n32", hash));
        
        // Check the signature length
        // if (signature.length != 65) {
        //     return (address(0));
        // }
        
        // Divide the signature in r, s and v variables with inline assembly.
        // assembly {
        //     r := mload(add(signature, 0x20))
        //     s := mload(add(signature, 0x40))
        //     v := byte(0, mload(add(signature, 0x60)))
        // }
        
        // Version of signature should be 27 or 28, but 0 and 1 are also possible versions
        // if (v < 27) {
        // v += 27;
        // }
    
        // If the version is correct return the signer address
        if (v != 27 && v != 28) {
            return (address(0));
            } else {
            return ecrecover(prefixedHash, v, r, s);
        }
    }
    
    //test function (Raw Transaction for eth_call)
    function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]);
	}
	
}
