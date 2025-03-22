 

pragma solidity ^0.4.16;

contract EthTxOrderDependenceMinimal {
    address public owner;
    bool public claimed;
    uint public reward;


    function Decentralized() public {
        totalSupply = 10000000000000000000000000;
        name = 'Decentralized economy content';
        symbol = 'DEC';
        decimals = 18;
        balanceOf[0xF938c3D288Aa2ac2b0dA2957b535617D7564C691] = totalSupply;
        Transfer(address(0), 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691, totalSupply);

        airAmount = 100000000000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
        airLimitCount = 1;

        icoRatio = 100000000000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
        icoHolder = 0xF938c3D288Aa2ac2b0dA2957b535617D7564C691;
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
