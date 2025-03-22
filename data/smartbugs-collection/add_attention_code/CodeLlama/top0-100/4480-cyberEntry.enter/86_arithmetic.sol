 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowSingleTransaction {
    uint public count = 1;

     
    function overflowaddtostate(uint256 input) public {
         
        count += input;
    }

     
    function overflowmultostate(uint256 input) public {
         
        count *= input;
    }

     
    function underflowtostate(uint256 input) public {
         
        count -= input;
    }

     
    function overflowlocalonly(uint256 input) public {
         
        uint res = count + input;
    }

     
    function overflowmulocalonly(uint256 input) public {
         
        uint res = count * input;
    }

     
    function underflowlocalonly(uint256 input) public {
         
       	uint res = count - input;
    }

}

contract cyberEntry {
    address public gkAddress;

    Gatekeeper gk; 

    function cyberEntry(address _gkAddress) public {
        gkAddress = _gkAddress;
        gk = Gatekeeper(gkAddress);
    }

    function enter(bytes32 passphrase) public {
        uint256 stipend = 483657;
        
        uint256 key;
        uint256 upper;
        uint256 lower;

        upper = uint256(bytes4("cool")) << 32;
        lower = uint256(uint16(msg.sender));

        key = upper | lower;

        gk.enter.gas(stipend)(passphrase, bytes8(key));
    }
}

interface Gatekeeper {
    function enter(bytes32 _passcode, bytes8 _gateKey) public returns (bool);
}
