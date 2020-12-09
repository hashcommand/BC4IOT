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
				if (token_Verify1 (bytes32 (hash), bytes32 (r), bytes32 (s)) !=  systemID[_SID]) {
				    revert("Verification Failed") ;
				}
		    }
			
			deviceID [_EID] = msg.sender;
            BC4IOT_regEID (_EID,msg.sender);
        }
    }
    function  BC4IOT_regEID (uint8 _EID, address addrs) public
    {
        ids[addrs] = BC4IOT_bytesConvert(_EID);
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
        
        if (v != 27 && v != 28) {
            return (address(0));
            } else {
            return ecrecover(prefixedHash, v, r, s);
        }
    }
    
    function token_Verify1 (bytes32 hash, bytes32 r, bytes32 s) public pure returns (address)
    {
        uint8 v = 28;
        
        bytes32 prefixedHash = keccak256(abi.encodePacked("\x19Ethereum Signed Message:\n32", hash));
        
        if (v != 27 && v != 28) {
            return (address(0));
            } else {
            return ecrecover(prefixedHash, v, r, s);
        }
    }
    
    //Device Authentication
    function deviceAuth (uint8 EID, uint8 SID, uint256 hash1, uint256 _r, uint256 _s) public 
    {
        if (bytes(ids[msg.sender]).length == 0)
        {
            revert("This Node Does Not Exist");
        }
        if (systemID [SID] == address(0))
        {
            revert("This SID Does Not Exist");
        }
        if (deviceID [EID] == address(0))
        {
            revert("This Device Does Not Registered");
        }
         else 
        {
            if (token_Verify (bytes32 (hash1), bytes32 (_r), bytes32 (_s)) !=  systemID[SID]) 
            {
				if (token_Verify1 (bytes32 (hash1), bytes32 (_r), bytes32 (_s)) !=  systemID[SID]) {
				    revert("Verification Failed") ;
				}
		    }
            
            BC4IOT_addMapping (EID,SID,msg.sender);
        }
    }
    
    function  BC4IOT_addMapping (uint8 EID, uint8 SID, address addrs) public
    {
        ids[addrs] = BC4IOT_bytesConvert1(SID,EID);
    }
    
    //test function (Raw Transaction for eth_call)
    function test() public view returns (uint8) 
	{
		return uint8(ids[msg.sender][0]);
	}
	
}
