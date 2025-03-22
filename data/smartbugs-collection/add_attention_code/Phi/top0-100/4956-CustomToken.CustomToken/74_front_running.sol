 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;


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

    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
    }
}
