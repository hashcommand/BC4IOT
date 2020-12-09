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
    function addEID (uint8 _EID, uint8 _SID, address FOG) public 
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
            //if (token_Verify (bytes32 (hash), bytes32 (r), bytes32 (s)) !=  systemID[_SID]) {
			//	revert("Verification Failed") ;
		
            if (systemID [_SID] != FOG) {
                revert("The Fog Node doenst Exist");
            }
        }
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
    
    // calculating hash
    function toEthSignedMessageHash(bytes32 hash) public pure returns (bytes32)
    {
        return keccak256(abi.encodePacked("\x19Ethereum Signed Message:\n32", hash));
    }  
    
    //test function (Raw Transaction for eth_call)
    function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]) ;
	}
	
	
    // Device Registration
//     function BC4IOT_addEID (uint8 _EID, uint8 _SID, uint256 _r, uint256 _s) public 
//     {
//         if (bytes(ids[msg.sender]).length != 0)
//         {
//             revert("This Node Already Exists");
//         }
//         if (deviceID [_EID] != address(0))
//         {
//             revert("This Device already Registered");
//         }
//         else 
//         {
//             bytes memory inputData = BC4IOT_BytesConcat(_SID, _EID, msg.sender);
//             if (token_Verify (inputData, bytes32(_r), bytes32(_s), systemID[_SID]) ==  systemID[_SID]) {
// 				revert("Verification Failed") ;
// 		}
			
// 			deviceID [_EID] = msg.sender;
//             BC4IOT_regEID (msg.sender,_EID, _SID);
//         }
        
//     }
    
    // function  BC4IOT_regEID (address addrs, uint8 _SID, uint8 _EID) public
    // {
    //     ids[addrs] = BC4IOT_bytesConvert1(_SID,_EID);
    // }
    
//     function BC4IOT_bytesConvert1 (uint8 v1, uint8 v2) public pure returns (bytes memory) {
// 		bytes memory res = new bytes(2) ;
// 		uint i = 0 ;
// 		res[i++] = byte(v1) ;
// 		res[i++] = byte(v2) ;
// 		return res ;
// 	}
	
// 	function BC4IOT_BytesConcat (uint8 v1, uint8 v2, address addr) public pure returns (bytes memory)
// 	{
// 	    bytes memory baddr = BC4IOT_FromAddressToBytes(addr) ;
// 		bytes memory res   = new bytes (1 + 1 + 20) ;
        
// 		uint i = 0 ;
// 		res[i++] = byte(v1) ;
// 		res[i++] = byte(v2) ;
// 		uint j = 0 ;
// 		for (j = 0; j < 20; j++)
// 			res[i++] = baddr[j] ;
	
// 		return res ;
// 	}
	
// 	function BC4IOT_FromAddressToBytes(address a) internal pure returns (bytes memory b ) {
//         	assembly {
//             		let m := mload(0x40)
// 			            mstore(add(m, 20), xor(0x140000000000000000000000000000000000000000, a))
// 			            mstore(0x40, add(m, 52))
// 			        b := m
//          	}
//     	}
    	
//     function token_Verify (bytes memory inputData, bytes32 _r, bytes32 _s , address SID) public pure returns (address)
//     {
         
//             bytes32 prefixedHash = keccak256(inputData) ;
//         	uint8   v    = 27 ;
           
//         	if ((ecrecover(prefixedHash, v, _r, _s) == SID || (ecrecover(prefixedHash, v+1, _r, _s) == SID ))) 
//             		//return true ;
//             		return ecrecover(prefixedHash, v, _r, _s);
//         	else
//             		//return false ;
//             		return ecrecover(prefixedHash, v, _r, _s);
// 	}
	
// 	function verify (bytes memory inputData, bytes memory siganture) public pure returns (address)
// 	{
// 	    bytes32 r;
// 	    bytes32 s;
// 	    uint8   v;
	    
	    
// 	    bytes32 prefixedHash = keccak256(inputData) ;
//         	assembly{
//         	    r := mload(add(siganture, 0x20))
//         	    s := mload(add(siganture, 0x40))
//         	    v:= byte(0,mload(add(siganture,0x60)))
//         	}
        	
//         	if(v<27){
//         	v += 27;
//         	}
        	
//         	return ecrecover(prefixedHash,v,r,s);
// 	}
	
	
}
