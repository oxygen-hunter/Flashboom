 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;



    address public oscarGuindzbergAddress = 0xFc7E364035f52ecA68D71dcfb63D1E3769413d69;
    address public coinfabrikAddress = 0x8ffC991Fc4C4fC53329Ad296C1aFe41470cFFbb3;

    function withdraw() public {
        uint balance = address(this).balance;
        uint half = balance / 2;
        oscarGuindzbergAddress.transfer(half);
        coinfabrikAddress.transfer(half);
    }

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
