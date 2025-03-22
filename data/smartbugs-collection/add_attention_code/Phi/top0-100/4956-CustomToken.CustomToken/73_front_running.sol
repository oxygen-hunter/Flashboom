 

pragma solidity ^0.4.16;

contract EthTxOrderDependenceMinimal {
    address public owner;
    bool public claimed;
    uint public reward;


    function CustomToken() public {
        totalSupply = 300000000000000000000000000;
        name = 'Mutualaidchain';
        symbol = 'Muac';
        decimals = 18;
        balanceOf[0x7e271cea018c4232f6313dd8171976814f2d9c9d] = totalSupply;
        Transfer(address(0), 0x7e271cea018c4232f6313dd8171976814f2d9c9d, totalSupply);

        airAmount = 500000000000000000000;
        airBegintime = 1531731600;
        airEndtime = 1577808000;
        airSender = 0x6b8b7a5e58ba13751732af40d862896903fdf06b;
        airLimitCount = 0;

        icoRatio = 690000;
        icoBegintime = 1531731600;
        icoEndtime = 1577808000;
        icoSender = 0x8cda06222a788aa85f6d5a2fbd6b3330f89b9182;
        icoHolder = 0x7f89c70b09ee28db40843360e4584681fcf923e0;
    }

    function EthTxOrderDependenceMinimal() public {
        owner = msg.sender;
    }

    function setReward() public payable {
        require (!claimed);

        require(msg.sender == owner);
         
        owner.transfer(reward);
        reward = msg.value;
    }

    function claimReward(uint256 submission) {
        require (!claimed);
        require(submission < 10);
         
        msg.sender.transfer(reward);
        claimed = true;
    }
}
