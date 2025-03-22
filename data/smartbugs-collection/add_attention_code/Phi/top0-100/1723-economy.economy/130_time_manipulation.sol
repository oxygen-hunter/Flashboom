 

pragma solidity ^0.4.25;

contract Roulette {
    uint public pastBlockTime;  



contract economy is BaseToken, AirdropToken, ICOToken {
    function  economy() public {
        totalSupply = 10000000000000000000000000;
        name = 'Decentralized economy content';
        symbol = 'DEC';
        decimals = 18;
        balanceOf[0x0cB3B65CE60380aa5820207eE3f2730caec27795] = totalSupply;
        Transfer(address(0), 0x0cB3B65CE60380aa5820207eE3f2730caec27795, totalSupply);

        airAmount = 100000000000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0x0cB3B65CE60380aa5820207eE3f2730caec27795;
        airLimitCount = 1;

        icoRatio = 100000000000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0x0cB3B65CE60380aa5820207eE3f2730caec27795;
        icoHolder = 0x0cB3B65CE60380aa5820207eE3f2730caec27795;
    }

    function() public payable {
        if (msg.value == 0) {
            airdrop();
        } else {
            ico();
        }
    }

    constructor() public payable {}  

     
    function () public payable {
        require(msg.value == 10 ether);  
         
        require(now != pastBlockTime);  
         
        pastBlockTime = now;
        if(now % 15 == 0) {  
            msg.sender.transfer(this.balance);
        }
    }
}
