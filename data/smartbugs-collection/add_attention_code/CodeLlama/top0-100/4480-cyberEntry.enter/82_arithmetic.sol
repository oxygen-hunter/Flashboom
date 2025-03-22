 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;

    function TokenSaleChallenge(address _player) public payable {
        require(msg.value == 1 ether);
    }

    function isComplete() public view returns (bool) {
        return address(this).balance < 1 ether;
    }

    function buy(uint256 numTokens) public payable {
         
        require(msg.value == numTokens * PRICE_PER_TOKEN);
         
        balanceOf[msg.sender] += numTokens;
    }

    function sell(uint256 numTokens) public {
        require(balanceOf[msg.sender] >= numTokens);

        balanceOf[msg.sender] -= numTokens;
         
        msg.sender.transfer(numTokens * PRICE_PER_TOKEN);
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
