 

pragma solidity ^0.4.19;
contract Token {
    function transfer(address _to, uint _value) returns (bool success);
    function balanceOf(address _owner) constant returns (uint balance);
}
contract EtherGet {
    address owner;


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