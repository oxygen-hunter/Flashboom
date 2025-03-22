 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);


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


     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }
