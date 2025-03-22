 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;

    constructor() {
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b184);
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b185);
    }

     
    function refundAll() public {
        for(uint x; x < refundAddresses.length; x++) {  
         
            require(refundAddresses[x].send(refunds[refundAddresses[x]]));  
        }
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
