 

pragma solidity ^0.4.24;

contract Missing{
    address private owner;

    modifier onlyowner {
        require(msg.sender==owner);
        _;
    }
     

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

    function Constructor()
        public
    {
        owner = msg.sender;
    }

    function () payable {}

    function withdraw()
        public
        onlyowner
    {
       owner.transfer(this.balance);
    }

}
