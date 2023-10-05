"use client";  // since useState is a client side hooks and next js is a server side language, so to implement this functionality we have use "use client"

import { useState, useEffect } from "react";

import styles from '../../styles/user.module.css'


const users = () => {
  const [users, activeUsers] = useState([]);
  const [loading, activeLoading] = useState(true); // track the loading condition
  const [error, activeError] = useState(null); // Display error if necessary

  useEffect(() => {
    fetching();
  }, []);

  const fetching = async () => {
    try {
      const response = await fetch("https://jsonplaceholder.typicode.com/users");  // using random api endpoint contaning user name and email
      const information = await response.json();
      activeUsers(information);
      activeLoading(false); // set false once the data is completely fetched
    } catch (error) {
      activeError("Failed to fetch data"); // Display error if data is not fetched successfully
      activeLoading(false); // set false once the data is completely fetched
    }
  };

  if (loading) {
    return <div>Loading...</div>; // Loading is displayed when the data is being fetched
  }

  if (error) {
    return <div>Error, {error}</div>; // Error message
  }

  return (
    <div className={styles.container}>
      <h1>Users Information</h1>
      <ol start={1}>
        {users.map((user, index) => (

          <li key={index} className={styles.list}>
            <b>Name:</b> {user.name} <br />
            <b>Email:</b> {user.email}
          </li>
        ))}
      </ol>
    </div>
  );
};

export default users;
