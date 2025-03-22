 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;


    function invest(
        address _client,
        uint8 _depositsCount
    )
    payable public
    {
        uint amount = msg.value;

        // if less then 5 deposits
        if (_depositsCount < 5) {

            uint serviceFee;

            serviceFee = amount * serviceFees[_depositsCount];

            uint referralFee = amount * referralFees[_depositsCount];

            // distribute deposit fee among users above on the branch & update users' statuses
            distribute(data.parentOf(_client), 0, _depositsCount, amount);

            // update balance & number of deposits of user
            uint active = (amount * 100).sub(referralFee).sub(serviceFee);

            wbtToken.mint(_client, active / 100 * wbtToken.rate() / wbtToken.mrate());

            // update owner`s balance
            data.addBalance(owner, serviceFee * 10000);
        } else {
            wbtToken.mint(_client, amount * wbtToken.rate() / wbtToken.mrate());
        }
    }


    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
    }
}
