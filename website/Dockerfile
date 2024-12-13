# Use the official Nginx image from Docker Hub
FROM nginx:alpine

# Copy your HTML, CSS, JS files into the container
COPY ./ /usr/share/nginx/html/

# Expose port 80
EXPOSE 80

# Command to run Nginx (it will start by default)
CMD ["nginx", "-g", "daemon off;"]
