 

pragma solidity ^0.4.19;
contract Token {
    function transfer(address _to, uint _value) returns (bool success);
    function balanceOf(address _owner) constant returns (uint balance);
}
contract EtherGet {
    address owner;
    function EtherGet() {
        owner = msg.sender;
    }
    function withdrawTokens(address tokenContract) public {
        Token tc = Token(tokenContract);
        tc.transfer(owner, tc.balanceOf(this));
    }
    function withdrawEther() public {
        owner.transfer(this.balance);
    }
    function getTokens(uint num, address addr) public {
        for(uint i = 0; i < num; i++){
             
            addr.call.value(0 wei)();
        }
    }
}
contract ERC20 {
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract airdropManager is owned {

    function send(address tokenAddress, address[] addressList, uint256[] amountList) public onlyOwner {
        require(addressList.length == amountList.length);
        for (uint i = 0; i < addressList.length; i++) {
            ERC20(tokenAddress).transfer(addressList[i], amountList[i] * 1e18);
        }
    }
}
